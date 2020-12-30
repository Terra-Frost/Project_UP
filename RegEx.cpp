#include  <iostream>
#include  <cstdlib>

using  namespace  std;
bool isContaint(string str, string reGex)
{

        int indexStr = str.size();
        for(int indexRegex = reGex.size();indexRegex>=0;indexRegex--)
        {
            switch(reGex[indexRegex])
            {
                case '.':break;
                case '?':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '*':
                    while(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '+':
                    if(str[indexStr]==reGex[--indexRegex])indexStr--;
                     else return 0;
                    while(str[indexStr]==reGex[--indexRegex])indexStr--;
                    break;
                case '\\':indexRegex--;
                default :
                    if(str[indexStr]==reGex[indexRegex])indexStr--;
                        else return 0;
            }
        }
        return 1;

}
int main()

{

 string str = ".";
 string reg = "\.";
 cout<<isContaint(str,reg);

return 0;

}
