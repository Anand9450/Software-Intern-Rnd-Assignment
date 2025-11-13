package com.example.flam_rnd_assignment;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.flam_rnd_assignment.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'flam_rnd_assignment' library on application startup.
    static {
        System.loadLibrary("flam_rnd_assignment");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'flam_rnd_assignment' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}