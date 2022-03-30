using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using DataContract;
using Microsoft.AspNetCore.Mvc;

// For more information on enabling Web API for empty projects, visit https://go.microsoft.com/fwlink/?LinkID=397860

namespace Server.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class DataController : ControllerBase
    {
        static Data data = new Data() { Nb = 21 };

        [HttpGet]
        public Data Get()
        {
            return data;
        }

        [HttpPost]
        [Route("AddData")]
        public void Post([FromBody] string valueToAdd) // Ca pourrait retourner le Data...mais ca ne me tente pas
        {
            data.Texts.Add(valueToAdd);
        }
    }
}
