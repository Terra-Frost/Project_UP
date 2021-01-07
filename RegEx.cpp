#include  <iostream>
#include  <cstdlib>
#include  <fstream>
using  namespace  std;
//Finding if a regex is corect,retuning appropriate errorcode if it's not
int normalize(string& reg)
{
    const string errorSymbols = "\\^.*+?";
    int numberOfSpeshalChar = 0;

    if(reg[reg.size()-1]=='\\') return -1;

    if(errorSymbols.find(reg[0],3) != string::npos)return -2;
    for(int i = 0; i < reg.size() ; i++)
    {
        // swaping the '\' and the escaped char so that there is easier to work with
        if(reg[i] == '\\')
        {

            if(errorSymbols.find(reg[i+1]) == string::npos) return -1;
            swap(reg[i],reg[i+1]);
            i++;
        }
        else
        {
            int specialSymbol = errorSymbols.find(reg[i],1);
            if(specialSymbol != -1)
            {
                if(specialSymbol > 2 && ++numberOfSpeshalChar >= 2) return -3;
                if(errorSymbols.find(reg[i+1],3) != string::npos) return -2;
            }
        }

        if(reg[i] == '^' && i != 0) return -4;

    }
    return 0;
}
// Checks if the regex matches a string from a index back
bool isContaint(string str, string reGex,int indexStr)
{
    for(int indexRegex = reGex.size()-1 ; indexRegex >= 0; indexRegex--)
    {
        switch(reGex[indexRegex])
        {
        case '^':
            if(str[indexStr] == '\n') return 1;
            else return 0;
            break;
        case '.':
            indexStr--;
            break;
        case '?':
            if(reGex[indexRegex-1] == '\\') indexRegex--;
            if(str[indexStr] == reGex[--indexRegex]) indexStr--;
            break;
        case '+':
            if(reGex[indexRegex-1] == '\\') indexRegex--;
            if(str[indexStr] == reGex[indexRegex-1]) indexStr--;
            else return 0;
        case '*':
            if(reGex[indexRegex] == '*' && reGex[indexRegex-1] == '\\') indexRegex--;
            indexRegex--;
            while(str[indexStr] == reGex[indexRegex] && indexStr >= 0)indexStr--;
            break;
        case '\\':
            indexRegex--;
        default :
            if(str[indexStr] == reGex[indexRegex])indexStr--;
            else return 0;
            break;
        }

    }
    return 1;

}
string errorCodeParser(int error)
{
    switch(error)
    {
    case -1:
        return "Not correct escape, either the symbol you are trying to escape can't be escaped or there is no symbol to be escaped\n";
    case -2:
        return "'?','+' or '*' is not used correctly before them is expected a non special char \n";
    case -3:
        return "more than two of '?','+','*' is a regex is not defined\n";
    case -4:
        return "'^' except in the beginning of a file is not permitted  \n";

    }
    return "Unexpected behavior";
}
bool findRegex(string str,string reg)
{
    str='\n'+str; // adding a symbol so it is easier to find where the beginning is

    for(int i = str.size()-1; i>=0; i--)
    {
        if(isContaint(str,reg,i)) return 1;
    }

    return 0;
}
int fReadStr(string filename, string& str, size_t line)
{
    //cout<<" -------"<<endl;
    ifstream MyFile(filename);
    if (!MyFile.is_open())return 1; // Unable to open file
    size_t lineNumber = 1;
    while ((lineNumber++ <= line) && (getline(MyFile,str)));
    if (MyFile.eof() && (line + 2 != lineNumber))
        return 2; // File is shorter than requested
    MyFile.close();
    return 0; // Success
}
int main()
{
    string regEx;
    string fileName;
    string str;
    cout<<"Regex: ";
    getline(cin,regEx);
    cout<<"File name: ";
    getline(cin,fileName);

    int errorCode = normalize(regEx);
    if(errorCode != 0)
    {
        cout<<errorCodeParser(errorCode);
        return 0;
    }
    int index = 1;
    do
    {
        switch(fReadStr(fileName,str,index))
        {
        case 0:

            if(findRegex(str,regEx))cout<<str<<endl;
            index++;
            break;
        case 1:
            cout<<1;
            return 0;
        case 2:
            return 0;
        }
        // cout<<str<<endl;

    }
    while(true);

    return 0;

}
