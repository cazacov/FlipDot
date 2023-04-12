using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BitsViewer
{
    class DumpRender
    {
        private readonly ListView listView;

        public DumpRender(ListView lvDump)
        {
            this.listView = lvDump;
        }

        public void Load(byte[] bytes)
        {
            this.listView.Items.Clear();

            this.listView.BeginUpdate();

            for (var i = 0; i < bytes.Length; i++)
            {
                var addr = i.ToString("X6");
                var dec = bytes[i].ToString();
                var hex = bytes[i].ToString("X2");

                var bits = Convert.ToString(bytes[i], 2);
                bits = bits.PadLeft(8, '0');

                ListViewItem item = new ListViewItem(addr);

                item.SubItems.AddRange(new string[] { dec, hex, bits });
                this.listView.Items.Add(item);

                /*
                if (i > 1000)
                {
                    break;
                }*/
            }
            this.listView.EndUpdate();
        }
    }
}
