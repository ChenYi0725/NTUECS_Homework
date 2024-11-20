package com.example.myapplication;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private EditText etFirstName, etLastName, etPhone;
    private TextView tvResult;
    private Button btnSubmit;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        etFirstName = findViewById(R.id.etFirstName);
        etLastName = findViewById(R.id.etLastName);
        etPhone = findViewById(R.id.etPhone);
        tvResult = findViewById(R.id.tvResult);
        btnSubmit = findViewById(R.id.btnSubmit);
        btnSubmit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String firstName = etFirstName.getText().toString().trim();
                String lastName = etLastName.getText().toString().trim();
                String phone = etPhone.getText().toString().trim();

                // 檢查輸入
                if (firstName.isEmpty()) {
                    tvResult.setText("名未輸入!");
                    tvResult.setTextColor(Color.RED);
                } else if (lastName.isEmpty()) {
                    tvResult.setText("姓未輸入!");
                    tvResult.setTextColor(Color.RED);
                } else if (phone.isEmpty()) {
                    tvResult.setText("電話未輸入!");
                    tvResult.setTextColor(Color.RED);
                } else {
                    String resultText = lastName + firstName + "的電話是" + phone;
                    tvResult.setText(resultText);
                    // 顏色
                    Random random = new Random();
                    int r = random.nextInt(256);
                    int g = random.nextInt(256);
                    int b = random.nextInt(256);

                    tvResult.setTextColor(Color.rgb(r, g, b));
                }
            }
        });
    }
}
