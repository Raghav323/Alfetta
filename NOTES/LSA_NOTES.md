**LSA CODE NOTES**

1. Macro :  Piece of code which is given some name and replaced in code during preprocessing (before compilation)
2. #define : Used to define a macro in c . A directive statement .
3. app_main() : Just like int main()
4. BLACK_MARGIN AND WHITE_MARGIN : macros defining upper and lower bounds for the readings from line sensors
5. CONSTRAINT_LSA_LOW AND CONSTRAINT LSA HIGH : values to which lsa readings are mapped to for convenience 
6. ADC : Analog to digital convertor . Converts analog values from photodiode to digital signals .Self explanatory .
7. Bound(val,min,max) : - Bounds the value to be in between min and max using simple if-else statements . Written inside utils.c in sra_board.h library 
8. Map(val,oldmin,oldmax,newmin,newmax) :- maps value which is bounded by oldmin , oldmax to new value bounded by newmin , newmax 
while maintaining equal spacing /uniformity using simple linear mathematics . Written inside utils.c in sra_board.h library.
9. enable_line_sensor() : enables line sensor and returns ESP_OK if successfull .Written inside lsa.c in sra_board.h library. Inside its definition , 
it calls enable_adc1() which uses adc.c library inside sra_board.h library to check if adc is enabled. 
10. read_line_sensor() : returns line sensor readings for all four pins . First sets the readings to zero ,then takes the average reading of a number of
samples for error reduction . Uses read_adc() written inside adc.c library inside sra_board.h library to read digital readings from adc.
11. vTaskDelay() : Explained in led blink notes
12. TAG : A constant static pointer pointing to a character array . It is the "tag" of the log
13. ESP_LOGI(tag,string,lsar1,lsar2,lsar3,lsar4) : A macro function defined inside esp_log.h which is used like printf to print lsa readings 
