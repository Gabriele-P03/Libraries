/**
 * 
 * @file
 * 
 * An element list represents the combination of children elements and cdata which are available for a certain element
 * 
 * An element list is composed by a LinkedList of elements - children -, a PRS_OP and a OCC_OP
 * 
 * @author Gabriele-P03
 */

#ifndef ELEMENTLIST_DTD_JPL
#define ELEMENTLIST_DTD_JPL

#include "Enums.hpp"
#define DEL_EFF_DS_JPL
#include <jpl/utils/structure/list/LinkedList.hpp>
#undef DEL_EFF_DS_JPL
#include "exception/DTDDuplicateException.hpp"

namespace jpl{
    namespace _parser{
        namespace _dtd{

            class Element;
            extern const std::string& getNameByElementPtr(const Element* element);

            struct Element_OCC{
                const Element* element;
                const OCC_OP occ;

                Element_OCC(Element* element, const OCC_OP &occ) : element(element), occ(occ){}
                ~Element_OCC(){
                    //delete this->element;//It does not have to delete element
                }
            };

            class ElementList{
                
                private:
                    _utils::_collections::_list::LinkedList<Element_OCC*>* elements;
                    _utils::_collections::_list::LinkedList<ElementList*>* elementLists;    //Sub conditional elements
                    PRS_OP prs;
                    OCC_OP occ;

                public:
                    ElementList() {
                        this->elements = new _utils::_collections::_list::LinkedList<Element_OCC*>();
                        this->elementLists = new _utils::_collections::_list::LinkedList<ElementList*>();
                        this->occ = jpl::_parser::_dtd::OCC_OP::MANDATORY;
                        this->prs = jpl::_parser::_dtd::PRS_OP::CHS;
                    }
                    ElementList(_utils::_collections::_list::LinkedList<Element_OCC*>* elements, 
                    _utils::_collections::_list::LinkedList<ElementList*>* elementLists, const PRS_OP &prs, const OCC_OP &occ){
                        this->elements = elements;
                        this->elementLists = elementLists;
                        this->prs = prs;
                        this->occ = occ;
                    }

                    const jpl::_utils::_collections::_list::LinkedList<Element_OCC*>* getElements() const noexcept{return this->elements;}
                    const jpl::_utils::_collections::_list::LinkedList<ElementList*>* getElementList() const noexcept{return this->elementLists;}

                    void setPRS_OP(const PRS_OP &prs) noexcept{this->prs = prs;}
                    const PRS_OP getPRS_OP() const noexcept {return this->prs;}
                    void setOCC_OP(const OCC_OP &occ) noexcept{this->occ = occ;}
                    const OCC_OP getOCC_OP() const noexcept {return this->occ;}

                    void addElementList(ElementList* elementList);
                    void addElement_OCC(Element_OCC* element_occ);

                    ~ElementList(){
                        delete this->elements;
                        delete this->elementLists;
                    }
            };

        }
    }
}

#endif
