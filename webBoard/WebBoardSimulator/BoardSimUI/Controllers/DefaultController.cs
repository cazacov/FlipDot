using BoardSimUI.DTOs;
using BoardSimUI.Processor;
using Microsoft.AspNetCore.Mvc;

namespace BoardSimUI.Controllers
{
    [ApiController]
    public class DefaultController : ControllerBase
    {
        private readonly ICommandProcessor commandProcessor;

        public DefaultController(ICommandProcessor commandProcessor)
        {
            this.commandProcessor = commandProcessor;
        }

        [HttpPost]
        [Route("/data")]
        public ActionResult<string> Data([FromBody] DataRequest dataRequest)
        {

            var command = new DataCommand();
            try
            {
                command.FrameBuffer = Convert.FromBase64String(dataRequest.FrameBuffer);
            }
            catch (ArgumentNullException)
            {
                return BadRequest("Missing mandatory frameBuffer parameter");
            }
            catch (FormatException)
            {
                return BadRequest("frameBuffer parameter is not a valid base64 encoded byte array");
            }

            if (commandProcessor.ProcessCommand(command, out var message))
            {
                return message;
            }
            else
            {
                return BadRequest(message);
            }
        }

        [HttpPost]
        [Route("/cls")]
        public ActionResult<string> Cls()
        {
            if (commandProcessor.ProcessCommand(new ClsCommand(), out var message))
            {
                return message;
            }
            else
            {
                return BadRequest(message);
            }
        }

        [HttpPost]
        [Route("/datablock")]
        public ActionResult<string> DataBlock([FromBody] DataBlockRequest dataRequest)
        {
            var command = new DataBlockCommand()
            {
                Left = dataRequest.Left,
                Top = dataRequest.Top,
                Width = dataRequest.Width,
                Height = dataRequest.Height
            };
            try
            {
                command.FrameBuffer = Convert.FromBase64String(dataRequest.FrameBuffer);
            }
            catch (ArgumentNullException)
            {
                return BadRequest("Missing mandatory frameBuffer parameter");
            }
            catch (FormatException)
            {
                return BadRequest("frameBuffer parameter is not a valid base64 encoded byte array");
            }

            if (commandProcessor.ProcessCommand(command, out var message))
            {
                return message;
            }
            else
            {
                return BadRequest(message);
            }

        }

        [HttpPost]
        [Route("/setblock")]
        public ActionResult<string> SetBlock([FromBody] BlockRequest dataRequest)
        {
            var command = new BlockCommand()
            {
                Left = dataRequest.Left,
                Top = dataRequest.Top,
                Width = dataRequest.Width,
                Height = dataRequest.Height
            };
            if (commandProcessor.ProcessCommand(command, out var message))
            {
                return message;
            }
            else
            {
                return BadRequest(message);
            }
        }

        [HttpPost]
        [Route("/textAdd")]
        public ActionResult<string> TextAdd([FromBody] AddTextRequest dataRequest)
        {
            var command = new AddTextCommand()
            {
                Text = dataRequest.Text,
                Left = dataRequest.Left,
                Bottom = dataRequest.Bottom,
                IsBig = dataRequest.IsBig
            };
            if (commandProcessor.ProcessCommand(command, out var message))
            {
                return message;
            }
            else
            {
                return BadRequest(message);
            }
        }
    }
}
