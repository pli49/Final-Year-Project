// Author: Laurence Prins
// Date: 26/06/2021
// Description: Serial commands

void showParsedData() {
    Serial.print("Selected function is: ");
    Serial.println(currFunction);
    Serial.print("Function inputs are: ");
    Serial.println(functionInputs);
}
