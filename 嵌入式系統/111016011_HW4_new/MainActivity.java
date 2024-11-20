package com.example.homrwork_4;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mainLayout = findViewById(R.id.mainLayout);
        radioGroupColors = findViewById(R.id.radioGroupColors);
        checkBoxDish1 = findViewById(R.id.checkBoxDish1);
        checkBoxDish2 = findViewById(R.id.checkBoxDish2);
        checkBoxDish3 = findViewById(R.id.checkBoxDish3);
        checkBoxDish4 = findViewById(R.id.checkBoxDish4);
        checkBoxDish5 = findViewById(R.id.checkBoxDish5);
        textViewPrice = findViewById(R.id.textViewPrice);


        disableCheckBoxes();

        radioGroupColors.setOnCheckedChangeListener((group, checkedId) -> {
            if (checkedId == R.id.radioRed) {
                mainLayout.setBackgroundColor(Color.RED);
            } else if (checkedId == R.id.radioGreen) {
                mainLayout.setBackgroundColor(Color.GREEN);
            } else if (checkedId == R.id.radioBlue) {
                mainLayout.setBackgroundColor(Color.BLUE);
            }
            // 啟用菜色選項
            enableCheckBoxes();
        });

        View.OnClickListener checkBoxListener = v -> updatePrice();

        checkBoxDish1.setOnClickListener(checkBoxListener);
        checkBoxDish2.setOnClickListener(checkBoxListener);
        checkBoxDish3.setOnClickListener(checkBoxListener);
        checkBoxDish4.setOnClickListener(checkBoxListener);
        checkBoxDish5.setOnClickListener(checkBoxListener);
    }


    private void updatePrice() {
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
            textViewPrice.setText("請選擇3或4種菜色");
        }
    }

    // 啟用CheckBox
    private void enableCheckBoxes() {
        checkBoxDish1.setEnabled(true);
        checkBoxDish2.setEnabled(true);
        checkBoxDish3.setEnabled(true);
        checkBoxDish4.setEnabled(true);
        checkBoxDish5.setEnabled(true);
    }


    private void disableCheckBoxes() {
        checkBoxDish1.setEnabled(false);
        checkBoxDish2.setEnabled(false);
        checkBoxDish3.setEnabled(false);
        checkBoxDish4.setEnabled(false);
        checkBoxDish5.setEnabled(false);
    }
}
