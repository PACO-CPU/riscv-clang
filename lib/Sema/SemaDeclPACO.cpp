//===------ SemaDeclPACO.cpp - Semantic Analysis for C++ Declarations -----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//  This file implements semantic analysis for PACO declarations.
//
//===----------------------------------------------------------------------===//

#include "clang/Sema/SemaInternal.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTMutationListener.h"
#include "clang/AST/CharUnits.h"
#include "clang/AST/DeclVisitor.h"
#include "clang/AST/EvaluatedExprVisitor.h"
#include "clang/AST/RecordLayout.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/StmtVisitor.h"
#include "clang/AST/TypeLoc.h"
#include "clang/AST/TypeOrdering.h"
#include "clang/Basic/PartialDiagnostic.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Sema/DeclSpec.h"
#include "clang/Sema/Initialization.h"
#include "clang/Sema/Lookup.h"
#include "clang/Sema/ParsedTemplate.h"
#include "clang/Sema/Scope.h"
#include "clang/Sema/ScopeInfo.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallString.h"
#include <map>
#include <set>

#include <stdio.h>

using namespace clang;

ApproxDecoratorDecl::KeyValue *ConvertNeglectToMask(ApproxDecoratorDecl::KeyValue *Key) {
  APValue newValue;
  uint64_t KeyData = *(Key->getNum().getInt().getRawData());
  switch(KeyData) {
    case(2): {
      newValue = APValue(llvm::APSInt(7, 0b1111110));
    }
    case(4): {
      newValue = APValue(llvm::APSInt(7, 0b1111100));
    }
    case(7): {
      newValue = APValue(llvm::APSInt(7, 0b1111000));
    }
    case(10): {
      newValue = APValue(llvm::APSInt(7, 0b1110000));
    }
    case(15): {
      newValue = APValue(llvm::APSInt(7, 0b1100000));
    }
    case(20): {
      newValue = APValue(llvm::APSInt(7, 0b1000000));
    }
    case(27): {
      newValue = APValue(llvm::APSInt(7, 0b0000000));
    }
  }
  return new ApproxDecoratorDecl::KeyValue(Key->getIdent(),newValue);
}

bool neglect_amout_valid(uint64_t num) {
    
    switch (num) {
    case 2:
    case 4:
    case 7:
    case 10:
    case 15:
    case 20:
    case 27:
        return true;
    }
    return false;
}

bool Sema::CheckApproxKeyVaule(SourceLocation ApproxLoc,
                         std::vector<ApproxDecoratorDecl::KeyValue*> keyvalues,
                         ApproxDecoratorDecl::KeyValue *newKey) {
    StringRef identName = StringRef(newKey->getIdent());

    if (identName.compare("neglect") == 0) {

      uint64_t num = newKey->getNum().getInt().getZExtValue();
      /* only valid values for neglect are allowed */
      if (!neglect_amout_valid(num)) {
        Diag(ApproxLoc, diag::err_approx_wrong_neglect_amount);
        return false;
      }

      for(size_t i=0;i<keyvalues.size();i++) {
        StringRef valueName = StringRef(keyvalues[i]->getIdent());

        /* Check if neglect already exits */
        if (valueName.compare("neglect") == 0) {
            Diag(ApproxLoc, diag::warn_approx_overide);
            keyvalues[i] = newKey;
            return true;
        /* If mask exits in the same approx decl give an error */
        } else if(valueName.compare("mask") == 0) {
            Diag(ApproxLoc,diag::err_approx_keyvalue_mask_neglect);
            return true;
        }
      } 
    } else if (identName.compare("mask") == 0) {
      for(size_t i=0;i<keyvalues.size();i++) {
        StringRef valueName = StringRef(keyvalues[i]->getIdent());

        /* Check if neglect already exits */
        if (valueName.compare("neglect") == 0) {
            Diag(ApproxLoc,diag::err_approx_keyvalue_mask_neglect);
            return true;
        /* If mask exits in the same approx decl give an error */
        } else if(valueName.compare("mask") == 0) {
            Diag(ApproxLoc, diag::warn_approx_overide);
            keyvalues[i] = newKey;
            return true;
        }
      }
    } else if (identName.compare("inject") == 0) {
      for(size_t i=0;i<keyvalues.size();i++) {
        StringRef valueName = StringRef(keyvalues[i]->getIdent());
        if(valueName.compare("inject") == 0) {
            Diag(ApproxLoc, diag::warn_approx_overide);
            keyvalues[i] = newKey;
            return true;
        }
      }
    } else if (identName.compare("relax") == 0) {
      for(size_t i=0;i<keyvalues.size();i++) {
        StringRef valueName = StringRef(keyvalues[i]->getIdent());
        if(valueName.compare("inject") == 0) {
            Diag(ApproxLoc, diag::warn_approx_overide);
            keyvalues[i] = newKey;
            return true;
        }
      }
    } else {
      Diag(ApproxLoc,diag::err_approx_keyvalue_not_valid);
      return false;
    }
    return true;
}
  

Decl *Sema::ActOnApproxDecorator(
  Scope *S,SourceLocation ApproxLoc,
  ApproxDecoratorDecl::KeyValue **keyvalues,
  size_t keyvalue_count) {
  ApproxDecoratorDecl *ADec = 0;

  ADec=ApproxDecoratorDecl::Create(Context,CurContext,ApproxLoc);

  for(size_t i=0;i<keyvalue_count;i++) {
    if (CheckApproxKeyVaule(ApproxLoc, ADec->getKeyValues(), keyvalues[i])) {
      if(StringRef(keyvalues[i]->getIdent()).compare("neglect") == 0)
        keyvalues[i] = ConvertNeglectToMask(keyvalues[i]);
      ADec->appendKeyValue(keyvalues[i]);
    }
  }
  return ADec;
}

ApproxDecoratorDecl::KeyValue *Sema::ActOnApproxDecoratorKeyValue(
  IdentifierInfo *ident, ExprResult exprNode, SourceLocation exprLoc) {

  Expr *expr=exprNode.get();
  Expr::EvalResult val;
  StringLiteral *lit;

  printf("  %s = ",ident->getNameStart());

  if (StringLiteral::classof(expr)) { // string key-value
    lit=reinterpret_cast<StringLiteral*>(expr);
    StringRef r=lit->getString();
    printf("'%.*s'\n",r.size(),r.data());
    return new ApproxDecoratorDecl::KeyValue(ident->getName().str(),lit->getString());

  } else { // numeric key-value
    if (!expr->EvaluateAsRValue(val,getASTContext())) {
      Diag(exprLoc,diag::err_approx_data_not_constant);
      return 0;
    }
    
    switch(val.Val.getKind()) {
      case APValue::Int:
        
        printf(
          "(int)%lli\n",
          (int64_t)val.Val.getInt().getLimitedValue());
        break;
      case APValue::Float:
        printf("(float)%g\n",val.Val.getFloat().convertToDouble());
        break;
      case APValue::ComplexInt:
        printf(
          "(cint)%lli + i*%lli\n",
          (int64_t)val.Val.getComplexIntReal().getLimitedValue(),
          (int64_t)val.Val.getComplexIntImag().getLimitedValue());
        break;
      case APValue::ComplexFloat:
        printf(
          "(cfloat)%g + i*%g\n",
          val.Val.getComplexFloatReal().convertToDouble(),
          val.Val.getComplexFloatImag().convertToDouble());
        break;
      default:
        Diag(exprLoc,diag::err_approx_data_not_num);
        return 0;
    }
    return new ApproxDecoratorDecl::KeyValue(ident->getName().str(),val.Val);
  }

}
