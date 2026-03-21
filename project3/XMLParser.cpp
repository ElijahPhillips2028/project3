#include "XMLParser.hpp"
#include <stdexcept>
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
	//must be both a token and done
	if(isDone == false || isToken == false){
		return false;
	}
	return elementNameBag.contains(inputString);
}

int XMLParser::frequencyElementName(const std::string &inputString) const
{
	//must be both a token and done
	if(isDone == false || isToken == false){
		throw std::logic_error("Is not done / is not a token");
	}
	return elementNameBag.getFrequencyOf(inputString);
}

