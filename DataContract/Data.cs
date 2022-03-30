using System;
using System.Collections.Generic;

namespace DataContract
{
    public class Data
    {
        // AB - pour faire la transition automatique de JSON, il est nécessaire d'avoir le {get;set;}
        public int Nb { get; set; }
        public List<string> Texts { get; set; } = new List<string>();
    }
}
