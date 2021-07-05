using System;
using System.IO;
using System.Linq;
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
            var exporter = new AdafruitFontExporter();

            if (!System.IO.Directory.Exists(args[1]))
            {
                System.IO.Directory.CreateDirectory(args[1]);
            }
            
            var bytes = System.IO.File.ReadAllBytes(args[0]);
            parser.Parse(bytes);

            foreach (var font in parser.Fonts.Values)
            {
                var maxHeight = font.Characters.Values.Max(x => x.Height);
                var minCode = font.Characters.Values.Min(x => x.Code);
                var maxCode = font.Characters.Values.Max(x => x.Code);
                Character refChar;
                if (font.Characters.ContainsKey(65))
                {
                    refChar = font.Characters[65];
                }
                else
                {
                    refChar = font.Characters.First().Value;
                }
                Console.Write($"{font.FontCode} - {font.Characters.Count}  [{minCode}-{maxCode}]");

                if (font.Characters.Count > 20)
                {
                    var targetDir = args[1];
                    var fontName = $"bus_{font.FontCode}_{refChar.Width}x{maxHeight}";
                    var fileBase = System.IO.Path.Combine(targetDir, fontName);
                    exporter.Export( fileBase+ ".h", fileBase + ".png", fontName, font, refChar);
                    Console.WriteLine($" -> {fontName}");
                }
                else
                {
                    Console.WriteLine($" skipped");
                }
            }
            return 0;
        }
    }
}
