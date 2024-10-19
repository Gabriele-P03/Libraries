#include "CSVParser.hpp"

jpl::_parser::_csv::CSVParser::CSVParser() : jpl::_parser::_csv::CSVParser(";") {}
jpl::_parser::_csv::CSVParser::CSVParser(const char* separator) : separator(separator){
    if(separator == nullptr)
        throw new jpl::_exception::IllegalArgumentException("Char separator is nullptr");
    this->multiTable = false;
}


void jpl::_parser::_csv::CSVParser::addTable(jpl::_utils::_collections::Table* table){
    if(table == nullptr)
        throw new jpl::_exception::IllegalArgumentException("You cannot add a nullptr");
    for(size_t i = 0; i < this->tables.getSize(); i++){
        jpl::_utils::_collections::Table* cr = this->tables.get(i);
        if(cr == table)
            throw new jpl::_exception::RuntimeException("This table has been already inserted");
        if(cr->getName().compare(table->getName()) == 0)
            throw new jpl::_exception::RuntimeException("There's already a table named as " + table->getName());
    }
    this->tables.add(table);
}


void jpl::_parser::_csv::CSVParser::parse(std::istream* is){
    std::string buffer;
    std::string line;
    while(std::getline(*is, line)){
        if(line.empty()){
            break;
        }else{
            buffer += line + "\n";
        }
    }
    this->parseHeader(buffer);
}


void jpl::_parser::_csv::CSVParser::parseHeader(std::string header){
    size_t i = 0, j;    //i -> table; j -> column
    bool check = !this->tables.isEmpty();   // (1)
    std::istringstream iss = std::istringstream(header);
    std::string tableDecl;
    size_t endSingleCol;
    while(std::getline(iss, tableDecl)){
        if(tableDecl.empty())
            continue;
        j = 0;
        jpl::_utils::_collections::Table* table;
        if(check){
            if(this->tables.getSize() <= i){    //Check if there are at least i-1 tables
                throw new jpl::_exception::RuntimeException("There are no enough tables into list");
            }
            table = this->tables.get(i++);
        }else{
            table = new jpl::_utils::_collections::Table(std::to_string(i++), true, true);    //Instance i-th table 
        }
        while ( (endSingleCol = tableDecl.find(this->separator) ) != std::string::npos){   //Each column
            std::string colName = tableDecl.substr(0, endSingleCol);
            if(colName.empty()){
                throw new jpl::_parser::_csv::_exception::CSVParsingException("There's an empty column name for the " + std::to_string(i) + " table");
            }
            tableDecl.erase(0, endSingleCol+1);
            if(check){
                if(table->getColumnsSize() <= j){
                    throw new jpl::_exception::RuntimeException("Table " + table->getName() + " has only " + std::to_string(table->getColumnsSize()) + " columns");
                }
                if(table->getColumn(j)->getName().compare(colName) != 0){
                    throw new jpl::_parser::_csv::_exception::CSVParsingException("Table " + table->getName() + " does not contain " + colName + " column");
                }
            }else{
                table->addColumn(new jpl::_utils::_collections::Column<std::string>(colName, false));
            }
            j++;
        }
        if(!check){
            this->tables.add(table);
        }
    }
}