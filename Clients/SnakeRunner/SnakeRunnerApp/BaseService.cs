using System;

using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Hosting;

namespace SnakeRunnerApp
{
    public abstract class BaseService : IHostedService
    {
        private Task workTask;
        protected readonly CancellationTokenSource stoppingToken = new CancellationTokenSource();

        public Task StartAsync(CancellationToken cancellationToken)
        {
            this.workTask = DoWorkAsync(stoppingToken.Token);
            
            // If the task is completed then return it,
            // this will bubble cancellation and failure to the caller
            if (workTask.IsCompleted)
            {
                Console.WriteLine($"{this.GetType().Name} background processing exited immediately.");
                return workTask;
            }

            // Otherwise it's running
            return Task.CompletedTask;

        }

        public async Task StopAsync(CancellationToken cancellationToken)
        {
            // Stop called without start
            if (workTask == null)
            {
                return;
            }
            try
            {
                // Signal cancellation to the executing method
                stoppingToken.Cancel();
            }
            finally
            {
                // Wait until the task completes or the stop token triggers
                await Task.WhenAny(workTask, Task.Delay(Timeout.Infinite, cancellationToken));
            }
        }

        protected abstract Task DoWorkAsync(CancellationToken cancellationToken);
    }
}
