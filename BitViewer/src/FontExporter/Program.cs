using System;
using System.Net.Mime;

namespace FontExporter
{
    class Program
    {
        static int Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.Error.WriteLine("Please provide file name");
                return -1;
            }

            var parser = new FontsParser();
            var bytes = System.IO.File.ReadAllBytes(args[0]);
            parser.Parse(bytes);
            var x = parser.Fonts;

            Console.WriteLine("Hello World!");
            return 0;
        }
    }
}
