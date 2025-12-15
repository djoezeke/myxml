/**
 * @file myxml.cppm
 * @brief File containing the module declaration for myxml.
 */

module;

#include <myxml/myxml.hpp>

export module myxml;

/**
 * @namespace myxml
 * @brief The myxml namespace myxml::
 */
export namespace myxml {

/**
 * @namespace literals
 * @brief The myxml namespace myxml::literals::
 */
inline namespace literals {

using ::myxml::literals::operator""_xml;

}  // namespace literals

using ::myxml::xml;

}  // namespace myxml
