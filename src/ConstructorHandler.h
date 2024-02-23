#pragma once

#include <regex>
// #include "ClangUtils.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Type.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/AST/Stmt.h"
#include "clang/AST/ExprCXX.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Frontend/FrontendActions.h"

#include "llvm/ADT/StringRef.h"

using namespace clang;
using namespace clang::ast_matchers;
using namespace llvm;

StatementMatcher ConstructorExprMatcher = cxxConstructExpr().bind("constructorExpr");

class ConstructorHandler : public MatchFinder::MatchCallback
{
public:
    explicit ConstructorHandler()
    {
    } //(WarningsManager& warningsM)

    virtual void run(const MatchFinder::MatchResult &Result)
    {
        const clang::CXXConstructExpr *expr = (clang::CXXConstructExpr *)Result.Nodes.getNodeAs<clang::CXXConstructExpr>("constructorExpr");
        if (expr)
        {
            const ASTContext *context = Result.Context;
            const SourceManager &sm = context->getSourceManager();
            llvm::StringRef fileName = sm.getFilename(sm.getSpellingLoc(expr->getBeginLoc()));
            if (std::regex_match(fileName.str(), std::regex("/usr/bin/.*")))
            {
                return;
            }
            CXXConstructorDecl *decl = expr->getConstructor();
            if (decl->isCopyConstructor() || decl->isConvertingConstructor(true))
            {
                const ASTContext *context = Result.Context;
                const SourceManager &sm = context->getSourceManager();
                reportCopy(Result, expr, context);
            }
        }
    }

    void reportCopy(const MatchFinder::MatchResult &Result, const clang::CXXConstructExpr *expr, const ASTContext *context)
    {
        DiagnosticsEngine &DE = context->getDiagnostics();

        unsigned diagID = DE.getCustomDiagID(DiagnosticsEngine::Warning, "copy constructor being called");
        DiagnosticBuilder DB = DE.Report(expr->getBeginLoc(), diagID);
        CharSourceRange range = CharSourceRange::getCharRange(expr->getSourceRange());
        DB.AddSourceRange(range);
    }
};
