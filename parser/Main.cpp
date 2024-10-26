//#define AUTO_LOG_EXCEPTION_JPL
#define USE_STACKTRACE_W_EXCEPTION_JPL
#include <jpl/logger/LoggerWrapper.hpp>
#include <jpl/utils/FilesUtils.hpp>
#include "src/csv/CSVParser.hpp"

#include "Test.cpp"


using namespace jpl;
using namespace _utils;
using namespace _parser;
using namespace _collections;
using namespace _list;

int main(){

    //Test(nullptr);
    /*
    std::ifstream in("/home/gabriele/JPL/parser/out/linux/test.csv");
    if(!in.is_open())
        exit(-1);
    
    */
    _csv::CSVParser csv = _csv::CSVParser(nullptr);
    //Table* table1 = new Table("1", true, true);
    //Table* table2 = new Table("2", true, true);
    /*
    Column<std::string>* col11 = new Column<std::string>("nome", false);
    Column<std::string>* col12 = new Column<std::string>("cognome", false);
    Column<std::string>* col13 = new Column<std::string>("età", false);
    Column<std::string>* col14 = new Column<std::string>("luogo", false);

    Column<std::string>* col21 = new Column<std::string>("x", false);
    Column<std::string>* col22 = new Column<std::string>("y", false);
    Column<std::string>* col23 = new Column<std::string>("z", false);
    

    table1->addColumn(col11);
    table1->addColumn(col12);
    table1->addColumn(col13);
    table1->addColumn(col14);

    table2->addColumn(col21);
    table2->addColumn(col22);
    table2->addColumn(col23);
    */
    //f(table2);
    //std::cout<<"ASAS";
    //csv.addTable(table1);
    //csv.addTable(nullptr);
    //csv.parse(&in);
}


