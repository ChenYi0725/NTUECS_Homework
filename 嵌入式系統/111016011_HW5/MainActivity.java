package com.example.a111016011_hw5;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private Spinner spinnerActivityType;
    private TextView textCalorieInfo, textCaloriesBurned;
    private EditText inputWeight, inputTime;
    private double caloriePerKgPerHour;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        spinnerActivityType = findViewById(R.id.spinner_activity_type);
        textCalorieInfo = findViewById(R.id.text_calorie_info);
        textCaloriesBurned = findViewById(R.id.text_calories_burned);
        inputWeight = findViewById(R.id.input_weight);
        inputTime = findViewById(R.id.input_time);

        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.activity_types, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinnerActivityType.setAdapter(adapter);


        spinnerActivityType.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if (position == 0){
                    caloriePerKgPerHour = 8.0;
                } else if (position == 1) {
                    caloriePerKgPerHour = 6.5;
                } else if (position == 2) {
                    caloriePerKgPerHour = 10.0;
                }

                textCalorieInfo.setText("消耗能量(千卡/公斤/小時): " + caloriePerKgPerHour);
                calculateCaloriesBurned();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) { }
        });


        inputWeight.addTextChangedListener(new InputWatcher());
        inputTime.addTextChangedListener(new InputWatcher());
    }


    private void calculateCaloriesBurned() {
        String weightText = inputWeight.getText().toString();
        String timeText = inputTime.getText().toString();

        if (!weightText.isEmpty() && !timeText.isEmpty()) {
            double weight = Double.parseDouble(weightText);
            double time = Double.parseDouble(timeText);
            double caloriesBurned = weight * time * caloriePerKgPerHour;
            textCaloriesBurned.setText("消耗能量 (千卡): " + caloriesBurned);
        } else {
            textCaloriesBurned.setText("消耗能量 (千卡): ");
        }
    }


    private class InputWatcher implements TextWatcher {
        @Override
        public void beforeTextChanged(CharSequence s, int start, int count, int after) { }

        @Override
        public void onTextChanged(CharSequence s, int start, int before, int count) {
            calculateCaloriesBurned();
        }

        @Override
        public void afterTextChanged(Editable s) { }
    }
}
