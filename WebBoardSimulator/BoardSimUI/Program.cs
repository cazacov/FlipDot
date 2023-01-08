using BoardSimUI.Processor;
using Microsoft.AspNetCore;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.DependencyInjection;

namespace BoardSimUI
{
    internal static class Program
    {
        public static MainForm MainForm;

        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main(string[] args)
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.

            var builder = CreateWebHostBuilder(args);
            var host = builder.Build();
            host.RunAsync();

            var serviceProvider = host.Services;

            //Application.SetHighDpiMode(HighDpiMode.SystemAware);
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            //ApplicationConfiguration.Initialize();
            
            MainForm = serviceProvider.GetRequiredService<MainForm>();
            Application.Run(MainForm);

        }

        private static IWebHostBuilder CreateWebHostBuilder(string[] args)
        {
            return WebHost
                .CreateDefaultBuilder(args)
                .UseStartup<Startup>()
                .UseUrls("http://localhost:5000/")
                .ConfigureServices((context, services) =>
                {
                    services.AddSingleton<MainForm>();
                    services.AddSingleton<ICommandProcessor>(x => x.GetRequiredService<MainForm>());
                });

        }
    }
}