using DataContract;
using Newtonsoft.Json;
using System;
using System.Net.Http;
using System.Text;
using System.Threading;

namespace Client
{
    class Program
    {
        static void Main(string[] args)
        {
            // AB - donner un certain temps d'attente pour que le serveur puisse se lancer correctement est une bonne idée
            Thread.Sleep(5000); 

            var serverAddr = Environment.GetEnvironmentVariable("SERVER_ADDR");

            if (serverAddr == null || serverAddr.Length == 0) // sans compter l'exception possible de l'appel plus haut, on essait de valider si on est capable d'obtenir la variable
            {
                Console.WriteLine("Varible d'environnnement invalide");
                return; // quitter le programme
            }

            using (var client = new HttpClient())
            {
                //////////////////
                // Get
                var returnValue = client.GetAsync(serverAddr + "/data").Result;

                if (!returnValue.IsSuccessStatusCode)
                {
                    Console.WriteLine("Communication Not OK");
                    return;
                }
                
                Console.WriteLine("Communication OK");
                var content = returnValue.Content.ReadAsStringAsync().Result;
                var data = JsonConvert.DeserializeObject<Data>(content);

                PrintData(data);

                //////////////////
                // Post
                SendString(client, serverAddr, "Hello");
                SendString(client, serverAddr, "World");
                SendString(client, serverAddr, "I'm");
                SendString(client, serverAddr, "Awesome");

                
                returnValue = client.GetAsync(serverAddr + "/data").Result;

                if (!returnValue.IsSuccessStatusCode)
                {
                    Console.WriteLine("Communication Not OK -- deuxieme GET");
                    return;
                }

                Console.WriteLine("Communication OK -- deuxieme GET");
                content = returnValue.Content.ReadAsStringAsync().Result;
                data = JsonConvert.DeserializeObject<Data>(content);

                PrintData(data);
            }
        }

        static bool SendString(HttpClient client, string serverAddr, string stringToSend)
        {
            var serialise = JsonConvert.SerializeObject(stringToSend);

            var toSend = new StringContent(serialise, Encoding.UTF8, "application/json");
            var response = client.PostAsync(serverAddr + "/data/adddata", toSend).Result;

            return response.IsSuccessStatusCode;
        }

        static void PrintData(Data data)
        {
            Console.WriteLine("Data ---------------------");
            Console.WriteLine(data.Nb);

            data.Texts.ForEach(elem => Console.WriteLine(elem)); // afficher pour chaque élément
            // a être honete, un foreach normal aurait bien préférable ici (...mais bon, c'est lefun faire des lambdas)

            Console.WriteLine("--------------------------");
        }
    }
}
