using Mailjet.Client;
using Mailjet.Client.Resources;
using System;
using Newtonsoft.Json.Linq;
namespace Mailjet.ConsoleApplication {
 class Program {
  static void Main(string[] args) {
   RunAsync().Wait();
  }
  static async Task RunAsync() {
   MailjetClient client = new MailjetClient(Environment.GetEnvironmentVariable("0717baf0866cc7e2dcb5cdd45d4087ad"), Environment.GetEnvironmentVariable("507902c46925593ddba6dc9f3530700e")) {
    Version = ApiVersion.V3_1,
   };
   MailjetRequest request = new MailjetRequest {
     Resource = Send.Resource,
    }
    .Property(Send.Messages, new JArray {
     new JObject {
      {
       "From",
       new JObject {
        {"Email", "opteamisprime@gmail.com"}, 
        {"Name", "Opteam"}
       }
      }, {
       "To",
       new JArray {
        new JObject {
         {
          "Email",
          "opteamisprime@gmail.com"
         }, {
          "Name",
          "Opteam"
         }
        }
       }
      }, {
       "Subject",
       "Greetings from Mailjet."
      }, {
       "TextPart",
       "My first Mailjet email"
      }, {
       "HTMLPart",
       "<h3>Dear passenger 1, welcome to <a href='https://www.mailjet.com/'>Mailjet</a>!</h3><br />May the delivery force be with you!"
      }, {
       "CustomID",
       "AppGettingStartedTest"
      }
     }
    });
   MailjetResponse response = await client.PostAsync(request);
   if (response.IsSuccessStatusCode) {
    Console.WriteLine(string.Format("Total: {0}, Count: {1}\n", response.GetTotal(), response.GetCount()));
    Console.WriteLine(response.GetData());
   } else {
    Console.WriteLine(string.Format("StatusCode: {0}\n", response.StatusCode));
    Console.WriteLine(string.Format("ErrorInfo: {0}\n", response.GetErrorInfo()));
    Console.WriteLine(response.GetData());
    Console.WriteLine(string.Format("ErrorMessage: {0}\n", response.GetErrorMessage()));
   }
  }
 }
}
