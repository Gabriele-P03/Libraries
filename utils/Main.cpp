#include "Main.hpp"

using namespace jpl;
using namespace _utils;
using namespace _collections;


int main(){

    Column<std::string>* col1 = new Column<std::string>("c1", true);
    Column<double>* col2 = new Column<double>("c2", false);
    Column<const char*>* col3 = new Column<const char*>("c3", true);
    Column<int>* col4 = new Column<int>("c4", false);

    Table* table = new Table("table", true, true);
    table->addColumn(col1);
    table->addColumn(col2);
    table->addColumn(col3);
    table->addColumn(col4);

    Tuple* tuple = new Tuple();
    table->addTuple(tuple);
    
    //TableWrapper::setStringValue(table, 0, 0, "cia");
    //TableWrapper::setStringValue(table, 0, 0, "cia1");
    TableWrapper::setSmartValue(table, 0, 0, "x");
}