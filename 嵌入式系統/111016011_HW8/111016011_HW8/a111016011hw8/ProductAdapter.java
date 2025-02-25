package com.example.a111016011hw8;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.TextView;

import java.util.List;

public class ProductAdapter extends ArrayAdapter<Product> {

    private Context context;
    private List<Product> products;

    public ProductAdapter(Context context, List<Product> products) {
        super(context, R.layout.item_product, products);
        this.context = context;
        this.products = products;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if (convertView == null) {
            convertView = LayoutInflater.from(context).inflate(R.layout.item_product, parent, false);
        }

        TextView tvName = convertView.findViewById(R.id.tvName);
        TextView tvPrice = convertView.findViewById(R.id.tvPrice);
        Button btnDelete = convertView.findViewById(R.id.btnDelete);

        Product product = products.get(position);
        tvName.setText(product.getName());
        tvPrice.setText(String.valueOf(product.getPrice()));

        btnDelete.setOnClickListener(v -> {

            SQLiteDatabase db = new ProductDatabaseHelper(context).getWritableDatabase();
            db.delete("product", "_id = ?", new String[]{String.valueOf(product.getId())});
            db.close();

            products.remove(position);
            notifyDataSetChanged();
        });

        return convertView;
    }
}
