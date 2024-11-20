package com.example.homrwork_4;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private View mainLayout;
    private RadioGroup radioGroupColors;
    private CheckBox checkBoxDish1, checkBoxDish2, checkBoxDish3, checkBoxDish4, checkBoxDish5;
    private TextView textViewPrice;
    private Button btnCheckout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mainLayout = findViewById(R.id.mainLayout); // 確認 mainLayout 的 ID
        radioGroupColors = findViewById(R.id.radioGroupColors);
        checkBoxDish1 = findViewById(R.id.checkBoxDish1);
        checkBoxDish2 = findViewById(R.id.checkBoxDish2);
        checkBoxDish3 = findViewById(R.id.checkBoxDish3);
        checkBoxDish4 = findViewById(R.id.checkBoxDish4);
        checkBoxDish5 = findViewById(R.id.checkBoxDish5);
        textViewPrice = findViewById(R.id.textViewPrice);
        btnCheckout = findViewById(R.id.btnCheckout);

        // 設定背景顏色的單選按鈕功能
        radioGroupColors.setOnCheckedChangeListener((group, checkedId) -> {
            if (checkedId == R.id.radioRed) {
                mainLayout.setBackgroundColor(Color.RED);
            } else if (checkedId == R.id.radioGreen) {
                mainLayout.setBackgroundColor(Color.GREEN);
            } else if (checkedId == R.id.radioBlue) {
                mainLayout.setBackgroundColor(Color.BLUE);
            }
        });

        // 結帳按鈕的功能
        btnCheckout.setOnClickListener(v -> {
            List<CheckBox> selectedDishes = new ArrayList<>();
            if (checkBoxDish1.isChecked()) selectedDishes.add(checkBoxDish1);
            if (checkBoxDish2.isChecked()) selectedDishes.add(checkBoxDish2);
            if (checkBoxDish3.isChecked()) selectedDishes.add(checkBoxDish3);
            if (checkBoxDish4.isChecked()) selectedDishes.add(checkBoxDish4);
            if (checkBoxDish5.isChecked()) selectedDishes.add(checkBoxDish5);

            int selectedCount = selectedDishes.size();
            if (selectedCount == 3) {
                textViewPrice.setText("價格：50元");
            } else if (selectedCount == 4) {
                textViewPrice.setText("價格：60元");
            } else {
                Toast.makeText(this, "請選擇3或4樣菜色", Toast.LENGTH_SHORT).show();
                textViewPrice.setText("價格：");
            }
        });
    }
}
