module Ajax = Rx_Ajax;
module Fetch = Rx_Fetch;
module Operators = Rx_Operators;
module Testing = Rx_Testing;
module WebSocket = Rx_WebSocket;

include Rx_Observable;
include Rx_Types;

[@bs.module "rxjs"] external pipe1: ('a, unaryFunction('a, 'b)) => 'b = "pipe";