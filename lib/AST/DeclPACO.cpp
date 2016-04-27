//===--- DeclPACO.cpp - C++ Declaration AST Node Implementation -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the PACO related Decl classes.
//
//===----------------------------------------------------------------------===//

#include "clang/AST/Decl.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTMutationListener.h"
#include "clang/AST/CXXInheritance.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/Expr.h"
#include "clang/AST/TypeLoc.h"
#include "clang/Basic/IdentifierTable.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallPtrSet.h"
using namespace clang;

ApproxDecoratorDecl::ApproxDecoratorDecl(
  DeclContext *DC, SourceLocation StartLoc) :
  Decl(ApproxDecorator,DC,StartLoc) {

}

ApproxDecoratorDecl *ApproxDecoratorDecl::Create(
  ASTContext &C, DeclContext *DC, SourceLocation StartLoc) {
  return new (C) ApproxDecoratorDecl(DC, StartLoc);
}

ApproxDecoratorDecl *ApproxDecoratorDecl::CreateDeserialized(
  ASTContext &C, unsigned ID) {
  void *Mem = AllocateDeserializedDecl(C, ID, sizeof(ApproxDecoratorDecl));
  return new (Mem) ApproxDecoratorDecl(0, SourceLocation());
}



