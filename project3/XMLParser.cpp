#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	isDone = false;
	isToken = false;
} 

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO
	return false;
} 

bool XMLParser::parseTokenizedInput()
{
	// TODO
	return false;
}

void XMLParser::clear()
{
	//clear the vector and the bag
	tokenizedInputVector.clear();
	elementNameBag.clear();
	//get rid of times in the stack
	while (!parseStack.isEmpty()) {
        parseStack.pop();
    }	
	//reset flags
	isDone = false;
	isToken = false;
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &inputString) const
{
	// TODO
	return false;
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	// TODO
	return -1;
}

