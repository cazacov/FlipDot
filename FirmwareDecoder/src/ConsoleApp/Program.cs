using System;
using System.Runtime.InteropServices;

namespace ConsoleApp
{
    class Program
    {
        static void Main(string[] args)
        {
            var bytes = System.IO.File.ReadAllBytes(args[0]);

            var render = new BitRender();

            var bitmap = render.DoRender(bytes);

            var fileName = System.IO.Path.GetFileNameWithoutExtension(args[0]);


            bitmap.Save($"C:\\Temporary\\{fileName}.png");
            bitmap.Dispose();
        }
    }
}
