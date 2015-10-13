/**
 * @file DllPort.hpp
 *
 * File containing a cpp macro that can be used to import or export symbol while using 
 * PgnParser as a dll.
 */
#ifndef INCLUDE_DLL_PORT_HPP_
#define INCLUDE_DLL_PORT_HPP_

#if defined(PGN_PARSER_EXPORT)
#  define DLLPORT __declspec(dllexport)
#elif defined(PGN_PARSER_IMPORT)
#  define DLLPORT __declspec(dllimport)
#else
#  define DLLPORT
#endif

#endif // INCLUDE_DLL_PORT_HPP_