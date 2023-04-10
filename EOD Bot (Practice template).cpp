// Define trading parameters
input double LotSize = 0.01; // trading volume
input int StopLoss = 50; // stop loss in pips
input int TakeProfit = 100; // take profit in pips

// Define EOD trading function
void EOD_Trading()
{
   // Get current time
   datetime current_time = TimeCurrent();
   
   // Check if it's end of day
   if (TimeHour(current_time) == 23 && TimeMinute(current_time) >= 55)
   {
      // Get current price
      double current_price = SymbolInfoDouble(_Symbol, SYMBOL_BID);
      
      // Calculate entry price
      double entry_price = current_price - StopLoss * _Point;
      
      // Calculate stop loss and take profit levels
      double stop_loss = entry_price - StopLoss * _Point;
      double take_profit = entry_price + TakeProfit * _Point;
      
      // Place buy order
      int ticket = OrderSend(_Symbol, OP_BUY, LotSize, entry_price, 0, stop_loss, take_profit, "EOD Trading", 0, 0, Green);
      
      // Check if order was successful
      if (ticket > 0)
      {
         Print("Buy order placed at ", entry_price);
      }
      else
      {
         Print("Error placing buy order: ", GetLastError());
      }
   }
}

// Define main function
void OnTick()
{
   // Call EOD trading function
   EOD_Trading();
}
