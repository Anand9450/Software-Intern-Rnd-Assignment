package com.example.flam_rnd_assignment;

import androidx.appcompat.app.AppCompatActivity;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'flam_rnd_assignment' library on application startup.
    static {
        System.loadLibrary("flam_rnd_assignment");
    }

    private ImageView myImageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myImageView = findViewById(R.id.my_image_view);

        // Load the test image from drawable
        Bitmap inBitmap = BitmapFactory.decodeResource(getResources(), R.drawable.test_image);

        // Create a mutable output bitmap
        Bitmap outBitmap = inBitmap.copy(Bitmap.Config.ARGB_8888, true);

        // Call the native C++ function
        detectEdges(inBitmap, outBitmap);

        // Display the processed image
        myImageView.setImageBitmap(outBitmap);
    }

    // Declare the native functions
    public native String stringFromJNI();
    public native void detectEdges(Bitmap inBitmap, Bitmap outBitmap);
}