package com.example.brain_teaser;


import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity
        implements AdapterView.OnItemClickListener {

    // 問題與答案陣列
    String[] queArr;
    String[] ansArr;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 從資源檔案中讀取問題與答案
        queArr = getResources().getStringArray(R.array.questions);
        ansArr = getResources().getStringArray(R.array.answers);

        // 建立供 ListView 使用的 ArrayAdapter 物件
        ArrayAdapter<String> adapter = new ArrayAdapter<>(
                this,
                android.R.layout.simple_list_item_1, // 使用內建的佈局資源
                queArr);                        // 以 queArr 陣列當資料來源

        ListView lv = findViewById(R.id.lv);  // 取得 ListView
        lv.setAdapter(adapter);              // 設定 ListView 使用的 Adapter
        lv.setOnItemClickListener(this);     // 設定 ListView 項目被按時的事件監聽器
    }

    @Override
    public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
        Toast.makeText(this,
                "答案︰" + ansArr[position], Toast.LENGTH_SHORT).show();
    }
}



