#include <iostream>
#include <vector>
using namespace std;

struct XMLAttributes
{
    string AttributeName,AttributeValue;
    
};


struct XMLELEMENT
{
    string tag,innerValue;
    
    vector<XMLELEMENT*>tags;
    vector<XMLAttributes*>attributes;
    bool hasSons;
         

};
XMLELEMENT* xmlParser(string xmlstr,int i );

void xmlAttributersParser(XMLELEMENT* xmlobject,string xmlstr,int i);
int main(){


cout<<"test from xml parser\n";


    string type="<xmlExample fAtt=\"dfv\" secAtt=\"vcvvc\">dfdf</xmlExample>";
xmlParser(type, 0 );
    return 0;
}
XMLELEMENT* xmlParser(string xmlstr,int i ){

    while (i<xmlstr.length())
    {
        if (xmlstr[i]=='<')
        {
            break;
        }
        ++i;
    }
//now moving to the name of the tag index start
++i;

    string TagName="";

    while (i<xmlstr.length())
    {
        if (xmlstr[i]=='>'||xmlstr[i]==' '||xmlstr[i]=='/')
        {
            break;
        }
        TagName+=xmlstr[i];
        ++i;
    }
    //moving to the next probable whitespace
    
    ++i;

    XMLELEMENT* element= new XMLELEMENT();
    element->tag=TagName;

 while (i<xmlstr.length())
    {
        if (xmlstr[i]!='>'||xmlstr[i]!=' '||xmlstr[i]!='/')
        {
            xmlAttributersParser(element,xmlstr,i);
            //if true this means the tag has no sons
            if (xmlstr[i]=='/')
            {
                element->hasSons=false;
            }
            
            break;
        }
    
        ++i;
    }
    
if (!element->hasSons)
{
    return element;
}


xmlAttributersParser(element,xmlstr,i);
    


}
void  xmlAttributersParser(XMLELEMENT* xmlobject,string xmlstr,int i)


{
//"<xmlExample fAtt=\"dfv\" secAtt=\"vcvvc\"/>";

int inParenthesses=0;
string AttributeName="";
string AttributeValue="";



 while (i<xmlstr.length())
    {
           
         if (inParenthesses>0&&(xmlstr[i]=='\"'||xmlstr[i]=='/'||xmlstr[i]=='>'))
        {
                  AttributeValue+=xmlstr[i];
             inParenthesses--;
                XMLAttributes* attribute= new XMLAttributes();
             attribute->AttributeName=AttributeName;
          
            for(int index=1;index<AttributeValue.length();++index){
                
                    if (AttributeValue[index]=='\"')
                    {
                        break;
                    }
                    

                attribute->AttributeValue+=AttributeValue[index];
            }
           
             xmlobject->attributes.push_back(attribute);
             AttributeValue="";
             AttributeName="";
              ++i;

        }
        if (inParenthesses<1&&xmlstr[i]=='\"')
        {
            inParenthesses++;

        }
        

    
        if (inParenthesses<1)
        {
             if (xmlstr[i]=='/'||xmlstr[i]=='>')
        {

         break;

        }
        
          if (xmlstr[i]!='='&&xmlstr[i]!=' ')
        {
         AttributeName+=xmlstr[i];

        }
         
        
    
        }else{
               AttributeValue+=xmlstr[i];
        }
        
     
        

            // inParenthesses--;
            // attribute->AttributeName=AttributeName;
            // attribute->AttributeValue=AttributeValue;
            // attributes.push_back(attribute);
            // AttributeName="";
            // AttributeValue="";
        

        
     
            
        

        

        


    
        ++i;
      
    }

    cout<<'\n'<<xmlstr[i];

}
