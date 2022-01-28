using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace ESP8266SnifferWebAPI.Controllers {

    // To make this local webapi visible to the internet, run
    //   ngrok http 43781 -host-header="localhost:43781

    [ApiController]
    [Route("[controller]")]
    public class SnifferController : ControllerBase {

        [HttpGet("{id:int}")]
        public string Get(int id) {
            return "Hello ESP8266";
        }


        // Receive tab delimited sniffed information in body of Http Post Reqeusr
        [HttpPost] 
        async public Task<string> Post() {
            var body = "";
            using (var reader = new System.IO.StreamReader(Request.Body)) {
                body = await reader.ReadToEndAsync();
            }


            // Chop payload up, and insert datestamp c
            var lines = body.Split("\r\n");
            var file = "";
            var dateStamp = DateTime.Now;           // We give the same datestamp to each entry in the batch, which is sort of ok
            foreach (var line in lines) {
                if(!String.IsNullOrWhiteSpace(line))
                    file += DateTime.Now.ToString("dd/MM/yyyy hh:mm:ss") + "\t" + line + "\r\n";
            }

            System.IO.File.AppendAllText("D:\\SniffedData.txt", file);
            return "Thanks for uploading ESP8266";
        }
    }
}
