using System;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

[XmlRootAttribute("PurchaseOrder", Namespace="http://www.cpandl.com", 
IsNullable = false)]
public class Key
{
   public string key;  
}

public class CreateKey {
    XmlSerializer serializer =  new XmlSerializer(typeof(PurchaseOrder));
    TextWriter writer = new StreamWriter("filename");
    Key key = new Key();
    key.key = "Hello World";
    serializer.Serialize(writer, key);
    writer.Close();
}