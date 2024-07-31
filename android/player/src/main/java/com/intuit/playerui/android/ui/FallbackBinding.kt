package com.intuit.playerui.android.ui

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.constraintlayout.widget.ConstraintLayout
import androidx.viewbinding.ViewBinding
import com.intuit.playerui.android.R

/**
 * This class is currently NOT automatically generated by the databinding/viewbinding,
 * That means any changes to the underlying layout file will not automatically update the available API
 */
public class FallbackBinding private constructor(
    private val rootView: ConstraintLayout,
    public val error: TextView,
    public val reset: Button,
    public val retry: Button,
    public val title: TextView,
) : ViewBinding {
    override fun getRoot(): ConstraintLayout {
        return rootView
    }

    public companion object {
        @JvmOverloads
        public fun inflate(
            inflater: LayoutInflater,
            parent: ViewGroup? = null,
            attachToParent: Boolean = false,
        ): FallbackBinding {
            val root = inflater.inflate(R.layout.fallback_view, parent, false)
            if (attachToParent) {
                parent!!.addView(root)
            }
            return bind(root)
        }

        public fun bind(rootView: View): FallbackBinding {
            val error = rootView.findViewById<TextView>(R.id.error)
            val reset = rootView.findViewById<Button>(R.id.reset)
            val retry = rootView.findViewById<Button>(R.id.retry)
            val title = rootView.findViewById<TextView>(R.id.title)

            return FallbackBinding(rootView as ConstraintLayout, error, reset, retry, title)
        }
    }
}
