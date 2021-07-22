/**
 * @file macro.h
 * @author andersonarc (e.andersonarc@gmail.com)
 * @version 0.1
 * @date 2021-07-04
 * 
 *  Macro for working with the preprocessor
 */
    /* header guard */
#ifndef CTOOL_MACRO_H
#define CTOOL_MACRO_H

    /* defines */
/**
 * Converts a single expression to a string
 * 
 * @param[in] x The expression
 */
#define _raw_macro_stringify(x) #x

/**
 * Expands a single expression and 
 * converts it to a string
 * 
 * @param[in] x The expression
 */
#define macro_stringify(x) _raw_macro_stringify(x)

#endif /* CTOOL_MACRO_H */