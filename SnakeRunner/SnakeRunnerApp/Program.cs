using System;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;

namespace SnakeRunnerApp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            CreateHostBuilder(args)
                .Build()
                .Run();
        }

        private static IHostBuilder CreateHostBuilder(string[] args)
        {
            var hostBuilder = Host.CreateDefaultBuilder(args)
                .ConfigureServices((b, c) =>
                {
                    c.AddHostedService<SnakeGame>();
                })
                .ConfigureLogging(logging =>
                {
                    logging.ClearProviders();
                });
            return hostBuilder;
        }
    }
}
