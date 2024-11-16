/**
 * @file
 * 
 * This is the representation of an XSD Namespace.
 * 
 * The namespace type is described by ns_type which can be DEFAULT in case of "xmlns", TARGET for "targetNamespace"
 * or even CUSTOM for "xmlns:target"
 *
 * 
 * @author Gabriele-P03
 */

#ifndef NAMESPACE_XSD_JPL
#define NAMESPACE_XSD_JPL

#include <string>

namespace jpl{
    namespace _parser{
        namespace _xsd{

            constexpr const char* NS_DEFAULT const = "xmlns";
            constexpr const char* NS_TARGET const = "targetNamespace";
            constexpr const char* NS_CUSTOM const = "xmlns:";   //After colons, there is the alias

            enum NamespaceType{
                DEFAULT,
                TARGET,
                CUSTOM
            };

            struct Namespace{

                const std::string ns;
                const std::string alias;
                const std::string value;
                const NamespaceType ns_type;

                Namespace(const NamespaceType ns_type, const std::string& ns, const std::string& alias, const std::string& value )
                    : ns_type(ns_type), ns(ns), alias(alias), value(value){}

                Namespace( const Namespace& namespace_ )
                    : Namespace(namespace_.ns_type, namespace_.ns, namespace_.alias, namespace_.value){}

                ~Namespace(){}
            }
        }
    }
}

#endif