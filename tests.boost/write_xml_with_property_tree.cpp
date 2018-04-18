#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//<Root>
//  <Set Name="1">
//      <Field Name="Hello 1"/>
//      <Field Name="World 1"/>
//  </Set>
//  <Set Name="2">
//      <Field Name="Hello 2"/>
//      <Field Name="World 2"/>
//  </Set>
//</Root>

int main(int argc, char* argv[])
{
    using boost::property_tree::ptree;
    ptree pt;

    boost::property_tree::ptree rootNode;
    boost::property_tree::ptree setNode1;
    boost::property_tree::ptree setNode2;
    boost::property_tree::ptree fieldNode1;
    boost::property_tree::ptree fieldNode2;
    boost::property_tree::ptree fieldNode3;
    boost::property_tree::ptree fieldNode4;

    fieldNode1.put("<xmlattr>.Name", "Hello 1");
    fieldNode2.put("<xmlattr>.Name", "World 1");
    fieldNode3.put("<xmlattr>.Name", "Hello 2");
    fieldNode4.put("<xmlattr>.Name", "World 2");

    setNode1.add_child("Field", fieldNode1);
    setNode1.add_child("Field", fieldNode2);
    setNode2.add_child("Field", fieldNode3);
    setNode2.add_child("Field", fieldNode4);

    setNode1.put("<xmlattr>.Name", "1");
    setNode2.put("<xmlattr>.Name", "2");

    rootNode.add_child("Set", setNode1);
    rootNode.add_child("Set", setNode2);
    pt.add_child("Root", rootNode);

    //    boost::property_tree::xml_writer_settings<char> settings('\t', 1);
    //    write_xml("testXml.xml", pt, std::locale(), settings);
    write_xml("testXml.xml", pt, std::locale());

    return 0;
}
