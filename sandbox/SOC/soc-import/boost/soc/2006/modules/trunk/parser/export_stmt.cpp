// export_stmt.cpp
#include "export_stmt.h"
#include "base_operations.h"
#include "lexpolicies.h"
#include "xformctx.h"
#include <boost/wave/token_ids.hpp>
#include <boost/format.hpp>

#include <iostream>

using namespace std;
using namespace boost::wave;
using boost::format;

/*
NOTES:
 - If we're in a partition, we shouldn't make the ["label"] part of the
   namespace name.  It should just be embedded namespace decls.
 - Multiple::Levels::Of::Nest should be translated to
   namespace Multiple { namespace Levels { namespace Of { namespace Nest {
   }}}} ---- Ignored now.  We're only putting out anonymous namespace names.
*/

//  std::string   m_mod_name;
//  enum mode { mExport, mNamespace, mModule, mFound } m_mode;

ExportStmtXForm::
ExportStmtXForm( const context_iter_t& start,
                 const context_iter_t& end )
 : TransformStage(start,end), m_mode (mExport) {
//  cerr << "[export_stmt(ctor)]" << endl; 
}

void 
ExportStmtXForm::
at_start (TransformContext *ctx) {
//  cerr << "[export_stmt: at_start]";
    ctx->start_hdr_emit ();
}

void 
ExportStmtXForm::
at_end (TransformContext * ctx) {
//  cerr << "[export_stmt: at_end]";
    ctx->stop_hdr_emit ();
}

OperationPair 
ExportStmtXForm::
process_token (const token_t& tok, TransformContext *ctx) {
//  cerr << "[tok]";
    OperationPair result;
    result.header = Operation::null_op;
    result.source = Operation::null_op;
    switch (m_mode) {
        // we eat the 'export namespace'
        case mExport: if (tok == T_EXPORT) { m_mode = mModule; }
            break;
//         case mNamespace: if (tok== T_NAMESPACE){ m_mode = mModule; }
//             break;
        // transform the module name into a
        // namespace ModuleName { (the rest is passed through, including the
        // closing brace)
        case mModule: {
            if (tok != T_LEFTBRACE) {
                // more module name to go through. just append it to our
                // module name
                if (tok == T_IDENTIFIER) 
                    m_mod_name.add_segment (tok);
                if (tok == T_STRINGLIT)
                	m_mod_name.set_partition(tok);
                break;
            } else {
                // just hit the opening brace of the module decl.
                // we have the full module name now, so we normalize it and
                // put out a formatted namespace statement.
                
                // first, register the original name, before we mangle it
                // all up.
                ctx->register_module(m_mod_name);
                
                // put out a readable decl.  we eat the opening curly brace,
                // so we emit one here. We reuse the existing closing curly
                // brace to close up.
                result.header = Operation_p (
                                    new StringOp (
                                       (format("\n// module %s\nnamespace {\n") 
                                               % m_mod_name.canonical () 
                                               // % m_mod_name.as_identifier ()).str()
                                       ).str () ));
                result.source = result.header;
                m_mode = mFound;
                break;              
            }
        }
        default: {
            result.header = Operation_p(new TokenOp(tok));
            result.source = result.header;
        }
    }
    return result;
}

OperationPair 
ExportStmtXForm::
process_upstream (OperationPair p, TransformContext *) {
//  cerr << endl << "[export_stmt: proc_upstream]" << endl;
    return p;
}

ExportStmtXForm::
~ExportStmtXForm () {}

const std::string& 
ExportStmtXForm::
get_identifier () {
	static std::string s_id("export_stmt");
	return s_id;
}

const std::string& 
ExportStmtXForm::
identifier () const {
	return get_identifier();
}

