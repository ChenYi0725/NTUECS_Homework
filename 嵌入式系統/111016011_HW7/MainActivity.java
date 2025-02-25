package com.example.a111016011_hw7;

import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        TextView pathView = findViewById(R.id.text_path);
        Button buttonToActivity2 = findViewById(R.id.button_to_activity2);
        Button buttonExit = findViewById(R.id.button_exit);


        String path = getIntent().getStringExtra("path");
        if (path == null) {
            path = "1";
        }

        pathView.setText("路徑: " + path);


        String finalPath = path;
        buttonToActivity2.setOnClickListener(v -> {
            Intent intent = new Intent(MainActivity.this, Activity2.class);
            intent.putExtra("path", finalPath + " -> 2 ");
            startActivity(intent);
        });


        buttonExit.setOnClickListener(v -> finish());
    }
}
