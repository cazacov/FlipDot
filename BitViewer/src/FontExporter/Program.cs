using System;
using System.Linq;

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

            if (args.Length < 3)
            {
                Console.Error.WriteLine("FontExporter.exe VERB ROMfile outputDir [parameters]");
                return -1;
            }

            var verb = args[0].ToLower();

            if (verb != "preview" && verb != "export")
            {
                Console.Error.WriteLine("Supported verbs: PREVIEW | EXPORT");
                return -1;
            }

            var romFile = args[1];
            var outputDir = args[2];
            if (!System.IO.Directory.Exists(outputDir))
            {
                System.IO.Directory.CreateDirectory(outputDir);
            }

            var bytes = System.IO.File.ReadAllBytes(romFile);
            parser.Parse(bytes);

            foreach (var font in parser.Fonts.Values)
            {
                var maxHeight = font.Characters.Values.Max(x => x.Height);
                var minCode = font.Characters.Values.Min(x => x.Code);
                var maxCode = font.Characters.Values.Max(x => x.Code);
                Character refChar;
                if (font.Characters.ContainsKey(48))
                {
                    refChar = font.Characters[48];
                }
                else
                {
                    refChar = font.Characters.First().Value;
                }
                Console.Write($"{font.FontCode} - {font.Characters.Count}  [{minCode}-{maxCode}]");

                if (verb == "preview" && font.Characters.Count > 10)
                {
                    var fontName = $"bus_{font.FontCode}_{refChar.Width}x{maxHeight}";
                    var fileBase = System.IO.Path.Combine(outputDir, fontName);
                    exporter.Preview( fileBase + ".png", font, refChar);
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
