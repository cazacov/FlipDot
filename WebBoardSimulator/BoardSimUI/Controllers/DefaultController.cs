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
    }
}
