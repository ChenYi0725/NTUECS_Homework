package com.example.a111016011_hw7;



import android.content.Intent;
import android.os.Bundle;
import android.widget.Button;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class Activity3 extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_3);

        TextView pathView = findViewById(R.id.text_path);
        Button buttonToMainActivity = findViewById(R.id.button_to_activity1);
        Button buttonExit = findViewById(R.id.button_exit);

        String path = getIntent().getStringExtra("path");

        if (path == null) {
            path = "Activity3";
        }
        pathView.setText("路徑: " + path);
        String finalPath = path;

        buttonToMainActivity.setOnClickListener(v -> {
            Intent intent = new Intent(Activity3.this, MainActivity.class);
            intent.putExtra("path", finalPath + " -> 1 ");
            startActivity(intent);
        });


        buttonExit.setOnClickListener(v -> finish());
    }
}
