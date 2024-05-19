# CppEllenallas project
#
# Originally created: 2023-03-06
#
# generate_warnings.cmake --
#   Ez a fájl definiál olyan segédfüggvényeket, amelyket a CMake projektek
#   felhasználnak a fordító figyelmeztetések bekapcsolására.

include(CheckCXXCompilerFlag)
include(CheckCCompilerFlag)

## CheckWarningFlag(lang OptionName CacheName) --
#
# Wrapper over check_(cxx|c)_compiler_flag that preprocesses the OptionName
# parameter to handle both GCC and MSVC style compiler flags:
# if a compiler flag starts with `/` it is passed as-is to the check,
# otherwise it is prepended with `-W`.
# The result of the flag will be saved to the `HAS_WARNING_${CacheName}`
# CMake cache variable.
#
# Lang can be either C or CXX.
function(check_warning_flag lang OptionName CacheName)
    if (OptionName MATCHES [[^/]]) # MSVC-style args are passed as-is
        set(WarningPrefix "")
    else ()
        set(WarningPrefix "-W")
    endif ()
    if (lang STREQUAL "C")
        check_c_compiler_flag("${WarningPrefix}${OptionName}" "HasWarning_${CacheName}")
    elseif (lang STREQUAL "CXX")
        check_cxx_compiler_flag("${WarningPrefix}${OptionName}" "HasWarning_${CacheName}")
    endif ()
    set("HAS_WARNING_${CacheName}" ${HasWarning_${CacheName}} PARENT_SCOPE)
endfunction()

## generate_warnings(lang &Target)
#
# Checks a set of warnings and their compatibility with the currently set compiler,
# and sets them for the given Target name's value.
# &Target is the name of the target to set the warnings for.
#
# The warnings are set at the public level.
#
# Lang can be either C or CXX.
function(generate_warnings lang _Target)
    set(gw_known_warnings
        # GCC/Clang
        extra pedantic error=vla error=non-virtual-dtor # error=lifetime
        error=trampolines parentheses logical-op reorder c++98-compat
        # MSVC
        /w14062 # enumerator 'identifier' in a switch of enum 'enumeration' is not handled
        /w14242 # 'identifier': conversion from 'type1' to 'type2', possible loss of data
        /we4263 # 'function': member function does not override any base class virtual member function
        /we4265 # 'class': class has virtual functions, but destructor is not virtual
        /w14287 # 'operator': unsigned/negative constant mismatch
        /w14296 # 'operator': expression is always false
        /we4350 # behavior change: 'member1' called instead of 'member2'
        /we4545 # expression before comma evaluates to a function which is missing an argument list
        /we4546 # function call before comma missing argument list
        /w14547 # 'operator': operator before comma has no effect; expected operator with side-effect
        /w14548 # expression before comma has no effect; expected expression with side-effect
        /w14549 # 'operator1': operator before comma has no effect; did you intend 'operator2'?
        /we4596 # 'identifier': illegal qualified name in member declaration
        /w14822 # 'member': local class member function does not have a body
        /we4837 # trigraph detected: '??character' replaced by 'character'
        /we4928 # illegal copy-initialization; more than one user-defined conversion has been implicitly applied
        /we4946 # reinterpret_cast used between related classes: 'class1' and 'class2'
        /we4986 # 'symbol': exception specification does not match previous declaration
        4
        /permissive-
        /diagnostics:caret)
    # MSVC /Wall turns on **every** warning, like Clang -Weverything
    set(gw_found_warnings $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall>)

    foreach (warn IN LISTS gw_known_warnings)
        string(MAKE_C_IDENTIFIER "${warn}" CacheName)
        check_warning_flag("${lang}" "${warn}" "${lang}${CacheName}")
        if (HAS_WARNING_${lang}${CacheName})
            if (warn MATCHES [[^/]]) # MSVC-style args are passed as-is
                set(WarningPrefix "")
            else ()
                set(WarningPrefix "-W")
            endif ()
            list(APPEND gw_found_warnings "${WarningPrefix}${warn}")
        endif ()
    endforeach ()

    target_compile_options("${_Target}" PUBLIC ${gw_found_warnings})
endfunction()