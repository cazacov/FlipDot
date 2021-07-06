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

            var fontCode = parser.Fonts.Values.First().FontCode;
            var fromChar = 32;
            var toChar = -1;
            var advance = 1;

            if (args.Length > 3)
            {
                Int32.TryParse(args[3], out fontCode);
            }
            if (args.Length > 4)
            {
                Int32.TryParse(args[4], out fromChar);
            }
            if (args.Length > 5)
            {
                Int32.TryParse(args[5], out toChar);
            }
            if (args.Length > 6)
            {
                Int32.TryParse(args[6], out advance);
            }


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

                var fontName = $"bus_{font.FontCode}_{refChar.Width}x{maxHeight}";
                var fileBase = System.IO.Path.Combine(outputDir, fontName);
                if (verb == "preview" && font.Characters.Count > 10)
                {
                    exporter.Preview( fileBase + ".png", font, refChar);
                    Console.WriteLine($" PREVIEW {fontName}");
                }
                else if (verb == "export" && font.FontCode == fontCode)
                {
                    exporter.Export(fileBase + ".h", font, fontName, refChar, fromChar, toChar, advance);
                    Console.WriteLine($" EXPORT {fontName}");
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
