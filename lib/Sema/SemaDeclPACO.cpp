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

CheckApproxKeyVaule(std::vector<ApproxDecoratorDecl::KeyValue*> *keyvalues, ApproxDecoratorDecl::KeyValue *newKey) {
  //TODOPACO: Add a check if keyvalues are valid
  switch(newKey->getIdent()){
    case "neglect": {
      for(size_t i=0;i<keyvalues.size;i++) {
        //TODOPACO: check if neglect already exists, if yes, override it
        //TODOPACO: check if mask and neglect exists in the same decl
      }
    }
    case "mask":{
      for(size_t i=0;i<keyvalues.size;i++) {
        //TODOPACO: check if mask already exists, if yes, override it
        //TODOPACO: check if mask and neglect exists in the same decl
      }
    }
    case "inject":{
      for(size_t i=0;i<keyvalues.size;i++) {
        //TODOPACO: check if inject already exists, if yes, override it
      }
    }
    case "relax":{
      //TODOPACO: check if mask and neglect exists in the same decl
      for(size_t i=0;i<keyvalues.size;i++) {
        //TODOPACO: check if relax already exists, if yes, override it
      }
    }
    default: {
      //TODOPACO: Add error message that there is no valid input
    }
  }
  
}

Decl *Sema::ActOnApproxDecorator(
  Scope *S,SourceLocation ApproxLoc,
  ApproxDecoratorDecl::KeyValue **keyvalues,
  size_t keyvalue_count) {
  ApproxDecoratorDecl *ADec = 0;

  ADec=ApproxDecoratorDecl::Create(Context,CurContext,ApproxLoc);

  for(size_t i=0;i<keyvalue_count;i++) {
    CheckApproxKeyVaule(ADec->getKeyValues(), keyvalues[i])
    ADec->appendKeyValue(keyvalues[i]);
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
    return new ApproxDecoratorDecl::KeyValue(ident,lit->getString());

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
    return new ApproxDecoratorDecl::KeyValue(ident,val.Val);
  }

}
