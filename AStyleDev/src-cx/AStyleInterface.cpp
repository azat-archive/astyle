#include "AStyleInterface.h"
#include <iostream>
#include <sstream>

/*
* The constructor sets the variable default values.
**/
AStyleInterface::AStyleInterface()
{   // bracket style options
    bracketStyle = STYLE_NONE;              // --style=?

    // tabs/spaces options
    indentType   = INDENT_SPACES;           // --indent=?, --indent=force-tab=#
    indentLength = 4;                       // --indent=?, --force-indent=tab=#
    useTabLength = false;                   // --indent=force-tab-x=#
    tabLength = 8;                          // --indent=force-tab-x=#

    // indentation options
    classIndent        = false;             // --indent-classes
    switchIndent       = false;             // --indent-switches
    caseIndent         = false;             // --indent-cases
    namespaceIndent    = false;             // --indent-namespaces
    labelIndent        = false;             // --indent-labels
    preprocessorIndent = false;             // --indent-preprocessor
    col1CommentIndent  = false;             // --indent-col1-comments
    maxInStatementIndent = 40;              // --max-instatement-indent=#
    minConditionalOption = MINCOND_TWO;     // --min-conditional-indent=#

    // padding options
    breakHeaderBlocks  = false;             // --break-blocks, --break-blocks=all
    breakClosingBlocks = false;             // --break-blocks=all
    padOperator        = false;             // --pad=oper
    padParenOutside    = false;             // --pad=paren, --pad=paren-out
    padFirstParenOut   = false;             // --pad-first-paren-out
    padParenInside     = false;             // --pad=paren, --pad=paren-in
    padHeader          = false;             // --pad-header
    unpadParen         = false;             // --unpad=paren
    deleteEmptyLines   = false;             // --delete-empty-lines
    fillEmptyLines     = false;             // --fill-empty-lines
    alignPointer       = PTR_ALIGN_NONE;    // --align-pointer= none, type, middle, name
    alignReference     = REF_SAME_AS_PTR;   // --align-reference= none, type, middle, name same as pointer

    // formatting options
    breakCloseBrackets = false;             // -- break-closing-brackets
    breakElseIfs       = false;             // --break-elseifs
    addBrackets        = false;             // --add-brackets
    addOneLineBrackets = false;             // --add-one-line-brackets
    breakOneLineStmts  = true;              // --one-line=keep-statements
    breakOneLineBlocks = true;              // --one-line=keep-blocks
    convertTabs        = false;             // --convert-tabs
    maxCodeLength      = 0;                 // --max-code-length=#
    breakAfterLogical  = false;             // --break-after-logical

    // file mode option
    fileMode = FILEMODE_CPP;                // --mode=?

    // save integer default values
    defaultIndentLength         = indentLength;
    defaultTabLength            = tabLength;
    defaultMinConditionalOption = minConditionalOption;
    defaultMaxInStatementIndent = maxInStatementIndent;
//    defaultMaxCodeLength        = maxCodeLength;
}

/**
* Display error messages for the class.
* This method should be changed to display messages in a manner consistent
* with the rest of the user program (e.g. a message box).
*
* @param  errorMessage   The error message to be displayed.
*/
void AStyleInterface::displayErrorMessage(string errorMessage)
{   cout << errorMessage << endl;
}

/**
* Build a string of options from the current option variables.
* An option is generated only if the current value is different
* than the default value.
* If an option variable is invalid, invalid text is sent to
* Artistic Style so the private ErrorHandler method will be called.
*
* @return    A string containing the options for Artistic Style.
*/
string AStyleInterface::getOptions() const
{   string options;                     // options to Artistic Style
    options.reserve(50);
    string separator = "\n";            // can be new-line, tab, space, or comma

    if (bracketStyle != STYLE_NONE)
    {   if (bracketStyle == STYLE_ALLMAN)
            options.append("style=allman");
        else if (bracketStyle == STYLE_JAVA)
            options.append("style=java");
        else if (bracketStyle == STYLE_KandR)
            options.append("style=k&r");
        else if (bracketStyle == STYLE_STROUSTRUP)
            options.append("style=stroustrup");
        else if (bracketStyle == STYLE_WHITESMITH)
            options.append("style=whitesmith");
        else if (bracketStyle == STYLE_BANNER)
            options.append("style=banner");
        else if (bracketStyle == STYLE_GNU)
            options.append("style=gnu");
        else if (bracketStyle == STYLE_LINUX)
            options.append("style=linux");
        else if (bracketStyle == STYLE_HORSTMANN)
            options.append("style=horstmann");
        else if (bracketStyle == STYLE_1TBS)
            options.append("style=1tbs");
        else if (bracketStyle == STYLE_PICO)
            options.append("style=pico");
        else if (bracketStyle == STYLE_LISP)
            options.append("style=lisp");
        else
            options.append("invalid-bracketStyle="      // force an error message
                           + intToString(bracketStyle));
        options.append(separator);
    }
    // begin indent check
    if (indentType == INDENT_SPACES)               // space is the default
    {   if (indentLength != defaultIndentLength)
        {   options.append("indent=spaces=" + intToString(indentLength));
            options.append(separator);
        }
    }
    else if (indentType == INDENT_TABS)             // tab is not the default
    {   if (indentLength == defaultIndentLength)
            options.append("indent=tab");
        else
            options.append("indent=tab=" + intToString(indentLength));
        options.append(separator);
    }
    else if (indentType == INDENT_FTABS)
    {   // check conditions to use default force-tab setting
        if (indentLength == defaultIndentLength)
        {   if (!useTabLength)
            {   options.append("indent=force-tab");
                options.append(separator);
            }
        }
        else
        {   options.append("indent=force-tab=" + intToString(indentLength));
            options.append(separator);
        }
        // check conditions to use different tab setting
        if (useTabLength)
        {   if (tabLength == defaultTabLength)
                options.append("indent=force-tab-x");
            else
                options.append("indent=force-tab-x=" + intToString(tabLength));
            options.append(separator);
        }
    }
    else
    {   options.append("invalid-indentType="       // force an error message
                       + intToString(indentType));
        options.append(separator);
    }
    // end indent check
    if (classIndent)
    {   options.append("indent-classes");
        options.append(separator);
    }
    if (switchIndent)
    {   options.append("indent-switches");
        options.append(separator);
    }
    if (caseIndent)
    {   options.append("indent-cases");
        options.append(separator);
    }
    if (namespaceIndent)
    {   options.append("indent-namespaces");
        options.append(separator);
    }
    if (labelIndent)
    {   options.append("indent-labels");
        options.append(separator);
    }
    if (preprocessorIndent)
    {   options.append("indent-preprocessor");
        options.append(separator);
    }
    if (col1CommentIndent)
    {   options.append("indent-col1-comments");
        options.append(separator);
    }
    if (maxInStatementIndent != defaultMaxInStatementIndent)
    {   options.append("max-instatement-indent="
                       + intToString(maxInStatementIndent));
        options.append(separator);
    }
    if (minConditionalOption != defaultMinConditionalOption)
    {   options.append("min-conditional-indent="
                       + intToString(minConditionalOption));
        options.append(separator);
    }
    // begin break-blocks check
    if (breakClosingBlocks)
    {   options.append("break-blocks=all");
        options.append(separator);
    }
    else if (breakHeaderBlocks)
    {   options.append("break-blocks");
        options.append(separator);
    }
    // end break-blocks check
    if (padOperator)
    {   options.append("pad-oper");
        options.append(separator);
    }
    // begin pad parens check
    if (padParenOutside && padParenInside)
    {   options.append("pad-paren");
        options.append(separator);
    }
    else if (padParenOutside)
    {   options.append("pad-paren-out");
        options.append(separator);
    }
    else if (padParenInside)
    {   options.append("pad-paren-in");
        options.append(separator);
    }
    // end pad parens check
    if (padFirstParenOut)
    {   options.append("pad-first-paren-out");
        options.append(separator);
    }
    if (padHeader)
    {   options.append("pad-header");
        options.append(separator);
    }
    if (unpadParen)
    {   options.append("unpad-paren");
        options.append(separator);
    }
    if (deleteEmptyLines)
    {   options.append("delete-empty-lines");
        options.append(separator);
    }
    if (fillEmptyLines)
    {   options.append("fill-empty-lines");
        options.append(separator);
    }
    if (alignPointer != PTR_ALIGN_NONE)
    {   if (alignPointer == PTR_ALIGN_TYPE)
            options.append("align-pointer=type");
        else if (alignPointer == PTR_ALIGN_MIDDLE)
            options.append("align-pointer=middle");
        else if (alignPointer == PTR_ALIGN_NAME)
            options.append("align-pointer=name");
        else
        {   options.append("align-pointer="        // force an error message
                           + intToString(alignPointer));
        }
        options.append(separator);
    }
    if (alignReference != REF_SAME_AS_PTR)
    {   if (alignReference == REF_ALIGN_NONE)
        {   options.append("align-reference=none");
            options.append(separator);
        }
        else if (alignReference == REF_ALIGN_TYPE)
        {   if (alignPointer != PTR_ALIGN_TYPE)
            {   options.append("align-reference=type");
                options.append(separator);
            }
        }
        else if (alignReference == REF_ALIGN_MIDDLE)
        {   if (alignPointer != PTR_ALIGN_MIDDLE)
            {   options.append("align-reference=middle");
                options.append(separator);
            }
        }
        else if (alignReference == REF_ALIGN_NAME)
        {   if (alignPointer != PTR_ALIGN_NAME)
            {   options.append("align-reference=name");
                options.append(separator);
            }
        }
        else
        {   options.append("align-reference="      // force an error message
                           + intToString(alignReference));
            options.append(separator);
        }
    }
    if (breakCloseBrackets)
    {   options.append("break-closing-brackets");
        options.append(separator);
    }
    if (breakElseIfs)
    {   options.append("break-elseifs");
        options.append(separator);
    }
    if (addBrackets)
    {   options.append("add-brackets");
        options.append(separator);
    }
    if (addOneLineBrackets)
    {   options.append("add-one-line-brackets");
        options.append(separator);
    }
    if (! breakOneLineStmts)                // default = true
    {   options.append("keep-one-line-statements");
        options.append(separator);
    }
    if (! breakOneLineBlocks)               // default = true
    {   options.append("keep-one-line-blocks");
        options.append(separator);
    }
    if (convertTabs)
    {   options.append("convert-tabs");
        options.append(separator);
    }
    if (maxCodeLength > 0)
    {   if (maxCodeLength >= MAX_CODE_LENGTH_MIN && maxCodeLength <= MAX_CODE_LENGTH_MAX)
            options.append("max-code-length=" + intToString(maxCodeLength));
        else
            options.append("invalid-maxCodeLength=" + intToString(maxCodeLength));
        options.append(separator);
        if (breakAfterLogical)
        {   options.append("break-after-logical");
            options.append(separator);
        }
    }
    // add the file mode, default is C++
    if (fileMode == FILEMODE_CPP)
    {   if (options.length() > 0)                  // delete the last separator
            options.erase(options.length() - 1);
    }
    else if (fileMode == FILEMODE_JAVA)
        options.append("mode=java");
    else if (fileMode == FILEMODE_SHARP)
        options.append("mode=cs");
    else
        options.append("invalid-fileMode="         // force an error message
                       + intToString(fileMode));

    return options;
}

/**
* Static method to convert int to a string.
* Not all compilers support the function itoa() (e.g. GCC).
*
* @param  intValue  The int to be converted.
*/
string AStyleInterface::intToString(int intValue)
{   ostringstream stringValue;
    stringValue << intValue;
    return stringValue.str();
}

/**
* Set the fileMode variable from the input file extension.
*
* @param  fileName   The name of the file, path may be included.
*/
void AStyleInterface::setFileMode(string fileName)
{   fileMode = FILEMODE_CPP;            // set the default
    size_t i = fileName.find_last_of('.');
    if (i != string::npos)
    {   string fileExtension = fileName.substr(i);
        if (fileExtension == ".java")
            fileMode = FILEMODE_JAVA;
        else if (fileExtension == ".cs")
            fileMode = FILEMODE_SHARP;
    }
}

/**
* Set options for testing.
* For test program only.
* This will not be used by an actual program.
*/
void AStyleInterface::setTestOptions()
{   // bracket Style options
    //bracketStyle = STYLE_ALLMAN;

    //// tabs / spaces options
    //indentType = INDENT_FTABS;
    //indentLength = 3;
    //useTabLength = true;
    //tabLength=6;

    //// indentation options
    //classIndent          = true;
    //switchIndent         = true;
    //caseIndent           = true;
    //namespaceIndent      = true;
    //labelIndent          = true;
    //preprocessorIndent   = true;
    //col1CommentIndent    = true;
    //maxInStatementIndent = 50;
    //minConditionalOption = 0;

    //// padding options
    //breakHeaderBlocks    = true;
    //breakClosingBlocks   = true;
    //padOperator          = true;
    //padParenOutside      = true;
    //padFirstParenOut     = true;
    //padParenInside       = true;
    //padHeader            = true;
    //unpadParen           = true;
    //deleteEmptyLines     = true;
    //fillEmptyLines       = true;
    //alignPointer         = PTR_ALIGN_TYPE;
    //alignReference       = REF_ALIGN_NAME;

    //// formatting options
    //breakCloseBrackets   = true;
    //breakElseIfs         = true;
    //addBrackets          = true;
    //addOneLineBrackets   = true;
    //breakOneLineBlocks   = false;
    //breakOneLineStmts    = false;
    //convertTabs          = true;
    //maxCodeLength        = 100;
    //breakAfterLogical    = true;

    //// generate some errors
    //bracketStyle    = (AStyleInterface::BracketStyle) 50;
    //maxInStatementIndent = 90;
    //minConditionalOption = 9;
    //// cannot have both invalid indentLength and invalid indentType
    //indentLength     = 21;
    //indentType         = (AStyleInterface::IndentType) 6;
}

// functions to call Artistic Style ---------------------------------------------------------------

/**
* Call the AStyleMain function in Artistic Style.
*
* @param   textIn  A pointer to the source code to be formatted.
* @return  A pointer to the formatted source from Artistic Style.
*/
char* AStyleInterface::formatSource(const char* textIn)
{   string options = getOptions();
    //displayErrorMessage("--------------------");
    //displayErrorMessage(options);
    //displayErrorMessage("--------------------");
    char* textOut = AStyleMain(textIn,
                               options.c_str(),
                               errorHandler,
                               memoryAlloc);
    return textOut;
}

/**
* Set fileMode and call the AStyleMain function in Artistic Style.
*
* @param   textIn  A pointer to the source code to be formatted.
* @param   fileName  A pointer to the name of the file being formatted.
* @return  A char pointer to the formatted source from Artistic Style.
*/
char* AStyleInterface::formatSource(const char* textIn, string& filePath)
{   // set file mode before formatting source
    setFileMode(filePath);
    char* textOut = formatSource(textIn);
    return textOut;
}

/**
* Set fileMode and call the AStyleMain function in Artistic Style.
*
* @param   textIn  A pointer to the source code to be formatted.
* @param   fileModeArg  A FileMode enum of the file being formatted.
* @return  A char pointer to the formatted source from Artistic Style.
*/
char* AStyleInterface::formatSource(const char* textIn, FileMode fileModeArg)
{   // set file mode before formatting source
    fileMode = fileModeArg;
    char* textOut = formatSource(textIn);
    return textOut;
}

/**
* Static method to handle error messages from messages from Artistic Style.
* This method is called only if there are errors when AStyleMain is called.
* This is for debugging and there should be no errors when the calling
* parameters are correct.
*
* @param  errorNumber   The error number from Artistic Style.
* @param  errorMessage  The error message from Artistic Style.
*/
void STDCALL AStyleInterface::errorHandler(int errorNumber, const char* errorMessage)
{   displayErrorMessage(string("astyle error "
                               + intToString(errorNumber)
                               + "\n" + errorMessage));
}

/**
* Allocate memory for the Artistic Style formatter.
* This method is called when Artistic Style needs to allocate memory.
* for the formatted file.
* The calling program is responsible for freeing the memory.
*
* @param  memoryNeeded  The amount of memory needed by Artistic Style.
*/
char* STDCALL AStyleInterface::memoryAlloc(unsigned long memoryNeeded)
{   // error condition should be checked by calling procedure
    char* buffer = new(nothrow) char [memoryNeeded];
    return buffer;
}
