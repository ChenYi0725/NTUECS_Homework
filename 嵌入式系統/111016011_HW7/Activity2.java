package com.example.a111016011_hw7;


import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class Activity2 extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_2);

        TextView pathView = findViewById(R.id.text_path);
        Button buttonToActivity3 = findViewById(R.id.button_to_activity3);
        Button buttonExit = findViewById(R.id.button_exit);


        String path = getIntent().getStringExtra("path");
        if (path == null) {
            path = "Activity2";
        }
        pathView.setText("路徑: " + path);
        String finalPath = path;

        buttonToActivity3.setOnClickListener(v -> {
            Intent intent = new Intent(Activity2.this, Activity3.class);
            intent.putExtra("path", finalPath + " -> 3 ");
            startActivity(intent);
        });

        buttonExit.setOnClickListener(v -> finish());
    }
}
