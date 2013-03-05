
// Copyright (C) 2008-2013 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#ifndef BOOST_CONTRACT_AUX_CALL_ARITY
#   error "INTERNAL ERROR: must define BOOST_CONTRACT_AUX_CALL_ARITY"
#endif
#ifndef BOOST_CONTRACT_AUX_CALL_IS_MEMBER
#   error "INTERNAL ERROR: must define BOOST_CONTRACT_AUX_CALL_IS_MEMBER"
#endif
#ifndef BOOST_CONTRACT_AUX_CALL_IS_STATIC
#   error "INTERNAL ERROR: must define BOOST_CONTRACT_AUX_CALL_IS_STATIC"
#endif
#ifndef BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR
#   error "INTERNAL ERROR: must define BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR"
#endif
#ifndef BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
#   error "INTERNAL ERROR: must define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY"
#endif
#ifndef BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
#   error "INTERNAL ERROR: must define BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT"
#endif

// The following code is fairly complex and hard to read due to the amount of
// preprocessor meta-programming that is used. This code was programmed this
// way so this one piece of code can generate *all* the call functions in order
// to *completely* avoid any code duplication in their implementations.
// Previous revisions or this code used to duplicate code among different call
// functions implementations but while these older revisions were more
// readable, they were very difficult to maintain because bug fixes and changes
// needed to be propagated among different part of the code. Therefore, all the
// call code was incorporated into this one meta-program (and it should be kept
// this way).
//
// The following code in general follows the conventions that #if-directives
// are used to turn on/off contract code blocks (via CONFIG macros) while
// PP-macros are used to pp meta-program the function code (this distinction
// was found to make this code a bit more readable).
//
// See also: include_.hpp, define_.hpp, undef_.hpp

template< class SignTraits >
BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY),
    // This generates a cons for constructor entry so no result allowed.
    typename SignTraits::result_type
)
BOOST_CONTRACT_func
(
#if BOOST_CONTRACT_AUX_CONFIG_DEBUG_01
    char const* file, unsigned long const& line, // Trailing comma `,`.
#endif
    BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
        // NOTE: Need to deduce this param because ISO C++ does not allow to
        // specify tparams for const (because invoked without a name).
        SignTraits
    ,
        typename SignTraits::body_type const body
    )
    BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_CALL_ARITY, BOOST_CONTRACT_comma_arg_param, ~)
    BOOST_PP_COMMA_IF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER,
            BOOST_PP_BITAND(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC),
                    BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))))
    BOOST_PP_EXPR_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER,
            BOOST_PP_BITAND(BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC),
                    BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))),
        typename SignTraits::cv_qualified_obj_type const obj
    )
#if BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && BOOST_CONTRACT_AUX_CALL_IS_MEMBER
    BOOST_PP_COMMA_IF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                    BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)))
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                    BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)),
        typename SignTraits::static_class_invariant_type const
                this_static_class_inv
    )
#   if !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    BOOST_PP_COMMA_IF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT))
    BOOST_PP_EXPR_IIF(BOOST_PP_BITOR(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR,
            BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT),
        typename SignTraits::class_invariant_type const this_class_inv
    )
#       if !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
    , typename SignTraits::
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC,
                static_class_invariant_type const sub_static_class_inv
            ,
                class_invariant_type const sub_class_inv
            )
#       endif
#   endif
#endif
#if BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
        && !BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
    , typename SignTraits::
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                static_precondition_type
            ,
                precondition_type 
            )
            const
            BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER,
                    BOOST_PP_BITAND(BOOST_PP_COMPL(
                            BOOST_CONTRACT_AUX_CALL_IS_STATIC), BOOST_PP_COMPL(
                            BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY))),
                sub_pre
            ,
                this_pre
            )
#endif
#if BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
        && !BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    , typename SignTraits::
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                constructor_oldof_type const this_cons_oldof
            , BOOST_PP_IIF(BOOST_PP_BITAND(BOOST_CONTRACT_AUX_CALL_IS_MEMBER,
                    BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)),
                subcontracted_oldof_type const sub_oldof
            ,
                oldof_type const this_oldof
            ))
#endif
) {
    if(call_globals<>::is_checking_contract)
    {
        BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                "Entering, executing body, and exiting function contract " <<
                "without checking contracts because assertions disabled " <<
                "within assertions " <<
                BOOST_PP_STRINGIZE(BOOST_CONTRACT_body_func))
        return
#if !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            BOOST_CONTRACT_body_func(
                BOOST_PP_ENUM(BOOST_CONTRACT_AUX_CALL_ARITY,
                        BOOST_CONTRACT_arg, ~)
            )
#endif
        ;
    }
    BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
            "Entering function contract")

    // POLICY: For constructors and destructors, subcontracting is realized by
    // the automatic invocation of all base constructor and destructor
    // contracts via C++ object creation and disposal mechanism so here we
    // just check this class constructor and destructor contract (not bases').

#if BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
        && BOOST_CONTRACT_AUX_CALL_IS_MEMBER \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    bool calling_body = false; // Used only for class inv.
    try
    {
#endif

    // Check class invariants on entry.
#if BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
        && BOOST_CONTRACT_AUX_CALL_IS_MEMBER \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
        // POLICY: Class inv are checked on entry/exit before pre/post so
        // pre/post assertions can be simplified assuming inv are true (e.g.,
        // don't check a ptr for nullity because inv already checked).
        // POLICY: Class inv are not checked if class inv func ptr is null so
        // caller can disable class inv checking for non public members.
        // POLICY: Destructor check this class inv (and not subcontracted ones)
        // because base class inv will be automatically invoked by C++ when
        // calling base destructors.
        if(
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC,
                sub_static_class_inv
            , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR,
                this_class_inv
            , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY,
                this_static_class_inv
            ,
                sub_class_inv
            )))
        ) {
            try
            {
                BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                        dbg << "Checking class invariants on entry " <<
                        BOOST_PP_STRINGIZE(BOOST_CONTRACT_entry_class_inv_func))
                call_globals<>::is_checking_contract = true;
                BOOST_CONTRACT_entry_class_inv_func();
                call_globals<>::is_checking_contract = false;
            }
            catch(...)
            { 
                BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_from,
                        dbg <<
                        "Calling class invariant broken handler on entry")
                call_globals<>::is_checking_contract = false;
                class_invariant_broken_on_entry(BOOST_CONTRACT_from);
            }
        }
#   if BOOST_CONTRACT_AUX_CONFIG_DEBUG_01
        else
        {
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Class invariant checking disabled on entry for " <<
                    "non-public member")
        }
#   endif
#endif

    // Check preconditions.
#if BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_01 \
        && !BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT
        try
        {
            // POLICY: By default, pre disable assertion checking globally like
            // any other contract checking func to avoid infinite recursion but
            // this can be changed for pre to comply with N1962.
#   if !BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Checking preconditions " <<
                    BOOST_PP_STRINGIZE(BOOST_CONTRACT_pre_func))
            call_globals<>::is_checking_contract = true;
#   else
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Checking preconditions configured to not disable " <<
                    "other assertions " <<
                    BOOST_PP_STRINGIZE(BOOST_CONTRACT_pre_func))
#   endif
            BOOST_CONTRACT_pre_func(
                // NOTE: Body func ptr is also passed to the contract checking
                // functions (pre, old-of, and post) to handle overloading.
                typename SignTraits::body_type()
                BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_CALL_ARITY,
                        BOOST_CONTRACT_comma_arg, ~)
            );
#   if !BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01
            call_globals<>::is_checking_contract = false;
#   endif
        }
        catch(...)
        {
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Calling precondition broken handler")
#   if !BOOST_CONTRACT_AUX_CONFIG_PRECONDITIONS_DISABLE_NO_ASSERTION_01
            call_globals<>::is_checking_contract = false;
#   endif
            precondition_broken(BOOST_CONTRACT_from);
        }
#endif

    // Copy old-ofs.
#if BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 \
        && !BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
        // POLICY: An exception thrown while evaluating and copying old-ofs
        // is threated as a post failure (while keeping the same active
        // exception that failed the old-of) because (1) class inv at entry and
        // pre passed so body can/should be executed but (2) old-ofs were not
        // copied so post cannot be checked.
        BOOST_PP_IIF(
                BOOST_PP_BITAND(
                      BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                    , BOOST_PP_BITAND(
                          BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                        , BOOST_PP_COMPL(
                                BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)
                      )
                ),
            std::list< typename SignTraits::bound_postcondition_type >
                    sub_post;
        ,
            typename SignTraits::bound_postcondition_type this_post;
        )
        bool oldof_failed = true;
        try
        {
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Evaluating and coping postcondition old-ofs (" <<
                    BOOST_PP_STRINGIZE(BOOST_CONTRACT_oldof_assignment_func) <<
                    ")")
            // POLICY: Disable all assertions also during old-of evaluation and
            // copy to prevent infinite recursion.
            call_globals<>::is_checking_contract = true;
            BOOST_CONTRACT_oldof_assignment_func(
                typename SignTraits::body_type()
                BOOST_PP_COMMA_IF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)
                BOOST_PP_EXPR_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                    obj
                )
                BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_CALL_ARITY,
                        BOOST_CONTRACT_comma_arg, ~)
            );
            call_globals<>::is_checking_contract = false;
            // NOTE: Following throw is used to jump to catch below (this trick
            // is necessary to keep eventual old-of error in active exception
            // to re-throw it later.
            throw oldof_failed = false;
        }
        catch(...)
        {
            // NOTE: Got here with oldof_failed == false iff no old-of error,
            // or with oldof_failed == true iff old-of error (in which case the
            // error is in the active exception).
            call_globals<>::is_checking_contract = false;
#endif

    // Call body (and copy result).
#if BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
        && BOOST_CONTRACT_AUX_CALL_IS_MEMBER \
        && !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            calling_body = true;
#endif
#   if BOOST_CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
            // POLICY: Only exceptions thrown by the body are handled by the
            // function (and constructor) try-block. In particular, contract
            // assertions and this library implementation code is executed
            // outside the function (and constructor) try-block (see N1962).
            // Function-try-blocks for functions other than constructors are
            // programmed outside the macros and just around the body
            // (constructors need special care because their member
            // initializers are programmed within the macros and constructor
            // try-blocks need to handle exceptions thrown by initializers).
            // NOTE: This enables constructor try-blocks also during
            // copy_result so eventual copy_result constructor exceptions
            // will also be handled by the try-block while ideally the
            // try-block will only handle body exceptions. However, copy_result
            // constructor simply calls the body and copies the result so no
            // exception but the one thrown by the body should be thrown.
            dynamic_cast< constructor_try_block_guard< typename
                    SignTraits::class_type > >(obj)->
                    BOOST_CONTRACT_AUX_SYMBOL((enable))();
#   endif
#if !BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && \
        !BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && \
        !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Executing body and returning without copying result " <<
                    BOOST_PP_STRINGIZE(BOOST_CONTRACT_body_func))
            // Optimization if no post (don't copy result).
            return BOOST_CONTRACT_body_func(
                BOOST_PP_ENUM(BOOST_CONTRACT_AUX_CALL_ARITY,
                        BOOST_CONTRACT_arg, ~)
            );
#elif !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Executing body and copying eventual result " <<
                    BOOST_PP_STRINGIZE(BOOST_CONTRACT_body_func))
            copy_result<
                typename SignTraits::result_type
                BOOST_PP_COMMA_IF(
                    BOOST_PP_BITAND(
                          BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                        , BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                    )
                )
                BOOST_PP_EXPR_IIF(
                        BOOST_PP_BITAND(
                              BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                            , BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                        ),
                    typename SignTraits::cv_qualified_obj_type
                )
            > result(
                  body // Result copy will call actual body.
                BOOST_PP_COMMA_IF(
                    BOOST_PP_BITAND(
                          BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                        , BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                    )
                )
                BOOST_PP_EXPR_IIF(
                        BOOST_PP_BITAND(
                              BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                            , BOOST_PP_COMPL(BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                        ),
                    obj
                )
                BOOST_PP_REPEAT(BOOST_CONTRACT_AUX_CALL_ARITY,
                        BOOST_CONTRACT_comma_arg, ~)
            );
#   if BOOST_CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
            dynamic_cast< constructor_try_block_guard< typename
                    SignTraits::class_type > >(obj)->
                    BOOST_CONTRACT_AUX_SYMBOL((disable))();
#   endif

    // Check class invariants on exit.
#   if BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 \
        && BOOST_CONTRACT_AUX_CALL_IS_MEMBER
            calling_body = false;

            // POLICY: For destructors, cannot check dynamic class inv because
            // there is no longer an object here after destructor body
            // execution but we can still check this static class inv (again,
            // do not check subcontracted static class inv because base static
            // class inv will be automatically invoked by C++ when calling base
            // destructors).
            if(
                BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC,
                    sub_static_class_inv
                , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR,
                    this_static_class_inv
                , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                    this_class_inv
                ,
                    sub_class_inv
                )))
            ) {
                BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                        dbg << "Checking class invariants on exit " <<
                        BOOST_PP_STRINGIZE(BOOST_CONTRACT_exit_class_inv_func))
                try
                {
                    call_globals<>::is_checking_contract = true;
                    BOOST_CONTRACT_exit_class_inv_func();
                    call_globals<>::is_checking_contract = false;
                }
                catch(...)
                {
                    BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                            dbg <<
                            "Calling class invariant on exit broken handler")
                    call_globals<>::is_checking_contract = false;
                    class_invariant_broken_on_exit(BOOST_CONTRACT_from);
                }
            }
#       if BOOST_CONTRACT_AUX_CONFIG_DEBUG_01
        else
        {
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Class invariant checking on exit disabled for " <<
                    "non-public member")
        }
#       endif
#   endif

    // Check postconditions.
#   if BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && !BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR
            try
            {
                if(oldof_failed)
                { 
                    BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                            dbg <<
                            "Unable to evaluate or copy old-of expressions (" <<
                            BOOST_PP_STRINGIZE(
                                    BOOST_CONTRACT_oldof_assignment_func) <<
                            ")")
                    throw; // Re-throw old-of error (from active exception).
                }
                BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                        dbg << "Checking postconditions (" <<
                        BOOST_PP_STRINGIZE(BOOST_CONTRACT_post_func) << ")")
                call_globals<>::is_checking_contract = true;
                BOOST_CONTRACT_post_func(
                    BOOST_PP_EXPR_IIF(
                            BOOST_PP_BITAND(
                                  BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                                , BOOST_PP_BITAND(
                                      BOOST_PP_COMPL(
                                            BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                                    , BOOST_PP_COMPL(
  BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)
                                  )
                            ),
                        sub_post
                    )
                    BOOST_PP_COMMA_IF(
                        BOOST_PP_AND(
                              BOOST_CONTRACT_AUX_CALL_ARITY
                            , BOOST_PP_BITAND(
                                  BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                                , BOOST_PP_BITAND(
                                      BOOST_PP_COMPL(
                                            BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                                    , BOOST_PP_COMPL(
  BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)
                                  )
                              )
                        )
                    )
                    BOOST_PP_ENUM(BOOST_CONTRACT_AUX_CALL_ARITY,
                            BOOST_CONTRACT_arg, ~)
                    BOOST_PP_COMMA_IF(
                        BOOST_PP_OR(
                              BOOST_CONTRACT_AUX_CALL_ARITY
                            , BOOST_PP_BITAND(
                                  BOOST_CONTRACT_AUX_CALL_IS_MEMBER
                                , BOOST_PP_BITAND(
                                      BOOST_PP_COMPL(
                                            BOOST_CONTRACT_AUX_CALL_IS_STATIC)
                                    , BOOST_PP_COMPL(
  BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT)
                                  )
                              )
                        )
                    )
                    result.param()
                );
                call_globals<>::is_checking_contract = false;
            }
            catch(...)
            {
                BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                        dbg << "Calling postcondition broken handler")
                call_globals<>::is_checking_contract = false;
                postcondition_broken(BOOST_CONTRACT_from);
            }
#   endif

            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Exiting function contract normally")
            return result.value();

#   if BOOST_CONTRACT_AUX_CONFIG_POSTCONDITIONS_01 && !BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR
        } // old-of catch
#   endif

#endif // !post01 && !inv && !cons_entry

    // Check class invariants on throw.
#if BOOST_CONTRACT_AUX_CONFIG_CLASS_INVARIANTS_01 && BOOST_CONTRACT_AUX_CALL_IS_MEMBER && \
        !BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
    }
    catch(...)
    {
#   if BOOST_CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
        // Make sure to disable try-block before checking invariants on exit.
        dynamic_cast< constructor_try_block_guard< typename
                SignTraits::class_type > >(obj)->
                BOOST_CONTRACT_AUX_SYMBOL((disable))();
#   endif
        // POLICY: Following exception safety guarantees, class inv (but not
        // post) are checked also when body throws.
        // If constructor body throws, only static class invariants can be
        // checked here (because constructor body was not able to create the
        // object).
        // If a destructor body throws (but note that following C++ STL
        // exception safety guarantees, destructors should be programmed to
        // never throw), subcontracted (to check that also base objects are in a
        // consistent state) class dynamic (because the destructor body failed
        // so the object was not destructed and it still exists) inv are
        // checked. However, if a destructor of one of the base classes throw
        // there is no way to go back and check the class invariants of the
        // derived classes (plus the derived constructor did not throw so the
        // derived part of the object is actually destructed) and in this case
        // the overall object is left only partially destructed and in an
        // undefined state (again, following exception safety rule destructors
        // should never throw so this should never happen).
        if(
            BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_STATIC,
                sub_static_class_inv
            , BOOST_PP_IIF(BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT,
                this_static_class_inv
            ,
                sub_class_inv
            ))
            && calling_body
        ) {
            try
            {
                try
                {
                    BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                            dbg << "Checking class invariants on throw " <<
                            BOOST_PP_STRINGIZE(
                                    BOOST_CONTRACT_throw_class_inv_func))
                    call_globals<>::is_checking_contract = true;
                    BOOST_CONTRACT_throw_class_inv_func();
                    call_globals<>::is_checking_contract = false;
                }
                catch(...)
                {
                    BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func,
                            dbg <<
                            "Calling class invariant on throw broken handler")
                    call_globals<>::is_checking_contract = false;
                    class_invariant_broken_on_throw(BOOST_CONTRACT_from);
                }
            }
            catch(...)
            {
                // NOTE: Re-throw eventual inv broken exception (this is needed
                // to allow the user to reprogram the contract handlers to
                // throw and exception instead of terminating).
                throw;
            }

            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Exiting function contract on throw")
            throw; // If invariant passed, re-throw body exception.
        }
#   if BOOST_CONTRACT_AUX_CONFIG_DEBUG_01
        else if(calling_body)
        {
            BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                    "Class invariant checking on throw disabled for " <<
                    "non-public member")
        }
#   endif
        BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
                "Exiting function contract on throw")
#   if BOOST_CONTRACT_AUX_IS_CONSTRUCTOR_EXIT
        if(calling_body)
        {
            // Enable constructor-try-block before re-throwing body exception.
            dynamic_cast< constructor_try_block_guard< typename
                    SignTraits::class_type > >(obj)->
                    BOOST_CONTRACT_AUX_SYMBOL((enable))();
        }
#   endif
        throw; // Re-throw (if no body call or no invariant checking).
    }
#endif
    BOOST_CONTRACT_AUX_DEBUGN(file, line, BOOST_CONTRACT_func, dbg <<
            "Exiting function contract normally")
}

// Undefine named external arg macros (similar to BOOST_PP_ITERATION_PARAMS).
#undef BOOST_CONTRACT_AUX_CALL_ARITY
#undef BOOST_CONTRACT_AUX_CALL_IS_MEMBER
#undef BOOST_CONTRACT_AUX_CALL_IS_STATIC
#undef BOOST_CONTRACT_AUX_CALL_IS_DESTRUCTOR
#undef BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_ENTRY
#undef BOOST_CONTRACT_AUX_CALL_IS_CONSTRUCTOR_EXIT

