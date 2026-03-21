#include "XMLParser.hpp"
#include <stdexcept>
XMLParser::XMLParser()
{
	isDone = false;
	isToken = false;
} 

bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	//make sure that the stack and bag is clear
    clear();
    
    int i = 0;
    int length = inputString.length();
    
    while (i < length) {
       //look for the < so show the start
        if (inputString[i] == '<') {
            int j = i + 1;
            
            //look for the > for the end
            while (j < length && inputString[j] != '>' && inputString[j] != '<') {
                j++;
            }
			//check if we run into a length issue for the < for a new line than throw false
            if (j == length || inputString[j] == '<') {
				//make sure next time works
                clear(); 
                return false; 
            }
            
           //get everything between the <>
            std::string tagContent = inputString.substr(i + 1, j - i - 1);
            TokenStruct t;
            
           //check what type of message it is 
            if (tagContent.length() >= 2 && tagContent.front() == '?' && tagContent.back() == '?') {
                //? mean deleraration
                t.tokenType = DECLARATION;
                //get tid of the ? to see the real string
                t.tokenString = tagContent.substr(1, tagContent.length() - 2);
            } 
            else if (!tagContent.empty() && tagContent.front() == '/') {
                //"/" is a end_tag
                t.tokenType = END_TAG;
              
                t.tokenString = tagContent.substr(1);
            } 
            else if (!tagContent.empty() && tagContent.back() == '/') {
                //empty_tag
                t.tokenType = EMPTY_TAG;
                // Strip the '/' from the back
                t.tokenString = tagContent.substr(0, tagContent.length() - 1);
            } 
            else {
                //start_tag
                t.tokenType = START_TAG;
                t.tokenString = tagContent;
            }

            tokenizedInputVector.push_back(t);
			//go to the next part after the > 
            i = j + 1;
			
        } 
        else {
            //go until the next tag
            int j = i;
           
            while (j < length && inputString[j] != '<') {
                j++;
            }
            
            std::string content = inputString.substr(i, j - i);
            
            //check for pure space
            bool allSpace = true;
            for (char conentChar : content) {
                if (!isspace(conentChar)) {
                    allSpace = false;
                    break;
                }
            }
            
            //make sure the text becomes a content token
            if (!allSpace) {
                TokenStruct token;
                token.tokenType = CONTENT;
                token.tokenString = content;
                tokenizedInputVector.push_back(token);
            }
            //move to the end
            i = j; 
        }
    }
    //update the flags
    isToken = true; 
    return true;
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

