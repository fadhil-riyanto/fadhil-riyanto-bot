#include "../submodule/pugixml/src/pugixml.hpp"
#include <iostream>
#include <ostream>

int main()
{
        std::string search = "_mm_abs_epi16";
        pugi::xml_document doc;
        pugi::xml_parse_result ret = doc.load_file("data-3-6-9.xml.xml");

        if (!ret)
                return -1;

        pugi::xml_node root_node = doc.child("intrinsics_list");

        for(pugi::xml_node intrin_arr = root_node.child("intrinsic"); intrin_arr; intrin_arr = intrin_arr.next_sibling("intrinsic")) {
                if (!search.compare(intrin_arr.attribute("name").as_string())) {
                        intrin_arr.attribute("name").as_string();
                }
        }
}