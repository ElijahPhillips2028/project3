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
	//looking through white spacees
	bool noWhiteSpace = false;
    for (char whiteChar : inputString) {
        if (!isspace(whiteChar)) {
            noWhiteSpace = true;
            break;
        }
    }
    if (noWhiteSpace == false) return false;

    while (i < length) {
       //look for the < so show the start
        if (inputString[i] == '<') {
            int j = i + 1;
            
            //look for the > for the end
            while (j < length && inputString[j] != '>' && inputString[j] != '<') {
				//looking for errors
				if (inputString[j] == '\n' || inputString[j] == '\r') {
                    clear();
                    return false;
                }
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
			else if (!tagContent.empty() && tagContent.front() == '!') {
                
                t.tokenType = DECLARATION; 
                t.tokenString = tagContent; 
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

				size_t spacePos = t.tokenString.find_first_of(" \t\n\r");
				if (spacePos != std::string::npos) {
   				t.tokenString = t.tokenString.substr(0, spacePos);
				}
            } 
            else {
                //start_tag
                t.tokenType = START_TAG;
                t.tokenString = tagContent;

				size_t spacePos = t.tokenString.find_first_of(" \t\n\r");
				if (spacePos != std::string::npos) {
  			  	t.tokenString = t.tokenString.substr(0, spacePos);
				}
            }
			if (t.tokenType == START_TAG || t.tokenType == END_TAG || t.tokenType == EMPTY_TAG) {
                if (t.tokenString.empty()) {
                    clear();
                    return false;
                }
                
                char firstChar = t.tokenString[0];
                if (!isalpha(firstChar) && firstChar != '_' && firstChar != ':') {
                    clear();
                    return false;
                }
                
                for (char tokenN : t.tokenString) {
                    if (!isalnum(tokenN) && tokenN != '_' && tokenN != '-' && tokenN != ':') {
                        clear();     
                        return false; 
                    }
                }
            }
            tokenizedInputVector.push_back(t)	;
			//go to the next part after the > 
            i = j + 1;
			
        } 
        else {
            //go until the next tag
            int j = i;
           
            while (j < length && inputString[j] != '<') {
				if (inputString[j] == '>') {
                    clear();
                    return false;
                }
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
            if (allSpace == false) {
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
	//must go to parse 
    if (isToken == false || tokenizedInputVector.empty()) {
        return false;
    }
    
    //clear the stack and bag
    while (parseStack.isEmpty() == false) parseStack.pop();
    elementNameBag.clear();
    
    int rootCount = 0;
    
    //go through all of the tokens
    for (const auto& token : tokenizedInputVector) {
        
        if (token.tokenType == START_TAG) {
            // Check if this is a top-level root element
            if (parseStack.isEmpty()) {
                rootCount++;
                if (rootCount > 1) return false; 
            }
            
            //put tags in the stack
            parseStack.push(token.tokenString);
            //put the names in the bag
            elementNameBag.add(token.tokenString);
        } 
        else if (token.tokenType == END_TAG) {
            //error check
            if (parseStack.isEmpty()) return false;
            if (parseStack.peek() != token.tokenString) return false;
            
            //if it does work than pop
            parseStack.pop();
        } 
        else if (token.tokenType == EMPTY_TAG) {
            // Empty tags can also be root elements
            if (parseStack.isEmpty()) {
                rootCount++;
                if (rootCount > 1) return false; 
            }
            
            //put the token in the bag
            elementNameBag.add(token.tokenString);
        }
        else if (token.tokenType == CONTENT) {
            // Text completely outside the root tag is invalid
            if (parseStack.isEmpty()) return false;
        }
    }
    
    // Valid XML must have an empty stack AND exactly 1 root element
    isDone = (parseStack.isEmpty() && rootCount == 1);
    return isDone;
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
		throw std::logic_error("not allowed");
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

