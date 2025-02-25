package com.example.a111016011hw8;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private ProductDatabaseHelper dbHelper;
    private List<Product> products;
    private ProductAdapter adapter;

    private EditText etName, etPrice;
    private Button btnAdd;
    private ListView listView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        dbHelper = new ProductDatabaseHelper(this);

        etName = findViewById(R.id.etName);
        etPrice = findViewById(R.id.etPrice);
        btnAdd = findViewById(R.id.btnAdd);
        listView = findViewById(R.id.listView);

        products = new ArrayList<>();


        btnAdd.setOnClickListener(v -> addProduct());

        // 載入產品清單
        loadProducts();
    }

    // 新增
    private void addProduct() {
        String name = etName.getText().toString().trim();
        String priceText = etPrice.getText().toString().trim();

        if (name.isEmpty() || priceText.isEmpty()) {
            Toast.makeText(this, "請輸入完整的產品名稱和價格", Toast.LENGTH_SHORT).show();
            return;
        }

        double price;
        try {
            price = Double.parseDouble(priceText);
        } catch (NumberFormatException e) {
            Toast.makeText(this, "價格必須為數字", Toast.LENGTH_SHORT).show();
            return;
        }

        SQLiteDatabase db = dbHelper.getWritableDatabase();
        ContentValues values = new ContentValues();
        values.put("name", name);
        values.put("price", price);

        long newRowId = db.insert("product", null, values);
        db.close();

        if (newRowId != -1) {
            Toast.makeText(this, "新增成功", Toast.LENGTH_SHORT).show();
            etName.setText("");
            etPrice.setText("");
            loadProducts();
        } else {
            Toast.makeText(this, "新增失敗", Toast.LENGTH_SHORT).show();
        }
    }

    // 產品清單
    private void loadProducts() {
        products.clear();

        SQLiteDatabase db = dbHelper.getReadableDatabase();
        Cursor cursor = db.query("product", null, null, null, null, null, null);

        while (cursor.moveToNext()) {
            int id = cursor.getInt(cursor.getColumnIndexOrThrow("_id"));
            String name = cursor.getString(cursor.getColumnIndexOrThrow("name"));
            double price = cursor.getDouble(cursor.getColumnIndexOrThrow("price"));
            products.add(new Product(id, name, price));
        }
        cursor.close();
        db.close();

        if (adapter == null) {
            adapter = new ProductAdapter(this, products);
            listView.setAdapter(adapter);
        } else {
            adapter.notifyDataSetChanged();
        }
    }
}
